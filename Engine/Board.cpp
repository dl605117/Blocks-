#include "Board.h"
#include <algorithm>

Board::Board()
	:
	rng( std::random_device()() ),
	choiceBlockPos( Vec2( Graphics::ScreenWidth - blockWidth,
		Graphics::ScreenHeight + 500.0f - blockHeight ) / 2 ),
	viewBlockPos( Vec2( Graphics::ScreenWidth - blockWidth - 40.0f,
	( Graphics::ScreenHeight + 500.0f - blockHeight ) / 2 ) )
{
}

Board::Board( const Board& brd )
	:
	score( brd.score )
{
	delete[] pPointSystem;
	pPointSystem = brd.pPointSystem;
}

Board::~Board()
{
	delete[] pPointSystem;
	pPointSystem = nullptr;
}

Board& Board::operator=( const Board brd )
{
	score = brd.score;

	delete[] pPointSystem;
	pPointSystem = brd.pPointSystem;

	return *this;
}

void Board::InitBoard()
{
	std::uniform_int_distribution<int> colorDist( 0,2 );
	viewBlock = std::make_unique<Block>(
		RectF( viewBlockPos,
			blockWidth,blockHeight ),
		blockColors[colorDist( rng )] );
	SpawnBlock();
}

void Board::PushColumn( int col )
{
	assert( !IsOver() );
	assert( choiceBlock != nullptr );
	animation = Animations::PushColumn;
	choiceBlock->LinearShift( Vec2( blockWidthDisplacement * ( col - nColumns / 2 ),0.0f ) );
	field[col].push_back( *choiceBlock );
	choiceBlock = nullptr;
	currentColPush = col;
}

void Board::SpawnBlock()
{
	if( !IsOver() )
	{
		timer = 0.0f;
		std::uniform_int_distribution<int> colorDist( 0,2 );
		choiceBlock = std::move( viewBlock );
		choiceBlock->SetLoc( choiceBlockPos );
		viewBlock = std::make_unique<Block>(
			RectF( viewBlockPos,
				blockWidth,blockHeight ),
			blockColors[colorDist( rng )] );
	}
}

void Board::Draw( Graphics& gfx ) const
{
	if( choiceBlock != nullptr )
	{
		choiceBlock->Draw( gfx );
		viewBlock->Draw( gfx );
	}
	for( std::vector<Block> col : field )
	{
		for( Block block : col )
		{
			block.Draw( gfx );
		}
	}
}

bool Board::IsOver() const
{
	for( std::vector<Block> col : field )
	{
		if( col.size() >= maxRows )
		{
			return true && !IsAnimating();
		}
	}
	return false;
}

void Board::UpdateAnimation( float dt )
{
	if( IsAnimating() )
	{
		switch( animation )
		{
		case Animations::PushColumn:
			PushAnimation( dt );
			break;
		case Animations::CollapseRow:
			CollapseAnimation( dt );
			break;
		case Animations::EraseRow:
			EraseAnimation( dt );
			break;
		}
	}
}

void Board::UpdateTimer( float dt )
{
	if( !IsOver() && !IsAnimating() )
	{
		timer += dt;
	}
	if( timer > maxTimer )
	{
		timer = 0;
		std::uniform_int_distribution<int> colDist(0,nColumns - 1);
		PushColumn( colDist( rng ) );
	}
}

void Board::UpdateBlocks()
{
	int minRows = int(field[0].size());
	for( std::vector<Block> col : field )
	{
		minRows = std::min( minRows,(int)col.size() );
	}

	int nCollapsedBlocks = 0;
	for( int row = 1; row < minRows + 1; row++ )
	{
		const Color colorMatch = field[0][field[0].size() - row].color;
		bool rowColorMatched = true;
		for( std::vector<Block> col : field )
		{
			rowColorMatched &= col[(int) col.size() - row].color == colorMatch;
		}
		if( rowColorMatched )
		{
			rowsToDelete.emplace_back( row );
			animation = Animations::EraseRow;
			nCollapsedBlocks++;
		}
	}
	if( animation != Animations::EraseRow )
	{
		SpawnBlock();
	}
	score += nCollapsedBlocks > 0 ? pPointSystem[nCollapsedBlocks - 1] : 0;
}

bool Board::IsAnimating() const
{
	return animation != Animations::NotAnimating;
}

void Board::PushAnimation( float dt )
{
	assert( animation == Animations::PushColumn );
	if( currentDisplacement >= blockHeightDisplacement )
	{
		UpdateBlocks();
		animation = animation == Animations::PushColumn ? 
			Animations::NotAnimating : animation;
		currentDisplacement = 0.0f;
	}
	else
	{
		auto movement = Vec2( 0.0f,-1.0f ) * animationSpeed * dt;
		const auto movementY = std::abs( movement.y );
		if( currentDisplacement + movementY > blockHeightDisplacement )
		{
			movement = Vec2( 0.0f, currentDisplacement - blockHeightDisplacement );
		}
		currentDisplacement += movementY;
		for( Block& block : field[(int) currentColPush] )
		{
			block.LinearShift( movement );
		}
	}
}

void Board::CollapseAnimation( float dt )
{
	assert( animation == Animations::CollapseRow );
	if( currentDisplacement >= blockHeightDisplacement )
	{
		currentDisplacement = 0.0f;
		SpawnBlock();
		rowsToDelete.clear();
		animation = Animations::NotAnimating;
	}
	else
	{
		auto movement = Vec2( 0.0f,1.0f ) * animationSpeed * dt;
		const auto movementY = std::abs( movement.y );
		if( currentDisplacement + movementY > blockHeightDisplacement )
		{
			movement = Vec2( 0.0f,blockHeightDisplacement - currentDisplacement );
		}
		currentDisplacement += movementY;
		for( std::vector<Block>& col : field )
		{
			auto tempRowsToDelete = rowsToDelete;
			for( int row : tempRowsToDelete )
			{
				for( int i = int( col.size() ) - row; i >= 0; i-- )
				{
					col[i].LinearShift( movement );
				}
				std::transform( tempRowsToDelete.begin(),
					tempRowsToDelete.end(),
					tempRowsToDelete.begin(),
					[]( int n )
				{
					return n - 1;
				} );
			}
		}
	}
}

void Board::EraseAnimation( float dt )
{
	assert( animation == Animations::EraseRow );
	if( currentDisplacement > animationEraseTimer )
	{
		animation = Animations::CollapseRow;
		currentDisplacement = 0;
		for( std::vector<Block>& col : field )
		{
			auto tempRowsToDelete = rowsToDelete;
			for( int row : tempRowsToDelete )
			{
				col.erase( col.end() - row );
				std::transform( tempRowsToDelete.begin(),
					tempRowsToDelete.end(),
					tempRowsToDelete.begin(),
					[]( int n )
				{
					return n - 1;
				} );
			}
		}
	}
	else
	{
		// using currentDisplacement as timer
		currentDisplacement += dt;
		for( std::vector<Block>& col : field )
		{
			for( int row : rowsToDelete )
			{
				col[(int) col.size() - row].color = Colors::Magenta;
			}
		}
	}
}

int Board::GetScore() const
{
	return score;
}

float Board::GetTimer() const
{
	return timer;
}

int Board::GetHeight() const
{
	return int( maxRows * ( blockHeight + blockHeightPadding ) + blockHeight );
}
int Board::GetWidth() const
{
	return int( ( nColumns - 1 ) * ( blockWidth + blockWidthPadding ) + blockWidth );
}

Vei2 Board::GetPos() const
{
	return Vei2( int( choiceBlockPos.x + ( blockWidth - GetWidth() ) / 2 ),
		int( choiceBlockPos.y + blockHeight - GetHeight() ) );
}