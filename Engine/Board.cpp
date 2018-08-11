#include "Board.h"
#include <algorithm>

Board::Board()
	:
	rng( std::random_device()() )
{
}

void Board::PushColumn( Column col )
{
	assert( !IsOver() );
	assert( choiceBlock != nullptr );
	choiceBlock->LinearShift( Vec2( 100.0f * ( (int) col - 1 ),0.0f ) );
	field[(int) col].push_back( *choiceBlock );
	choiceBlock = nullptr;
	currentColPush = col;
	animation = Animations::PushColumn;
}

void Board::SpawnBlock()
{
	std::uniform_int_distribution<int> colorDist( 0,2 );
	choiceBlock = std::make_unique<Block>(
		RectF( Vec2( Graphics::ScreenWidth - blockWidth,
			Graphics::ScreenHeight + 500 - blockHeight ) / 2,
			blockWidth,blockHeight),
			blockColors[colorDist( rng ) ] );
}

void Board::Draw( Graphics& gfx )
{
	if( choiceBlock != nullptr )
	{
		choiceBlock->Draw( gfx );
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

void Board::UpdateBlocks()
{
	int minRight = std::min(
		int( field[(int) Column::Right].size() ),
		int( field[(int) Column::Middle].size() ) );
	int minRows = std::min(
		int( field[(int) Column::Left].size() ),minRight );

	bool collapsedBlocks = false;
	for( int row = 1; row < minRows + 1; row++ )
	{
		const Color matchColor = field[(int) Column::Left][field[0].size() - row].color;
		if( field[(int) Column::Middle][field[1].size() - row].color == matchColor
			&& field[(int) Column::Right][field[2].size() - row].color == matchColor )
		{
			rowsToDelete.emplace_back( row );
			animation = Animations::EraseRow;
			collapsedBlocks = true;
		}
	}
	if( !collapsedBlocks )
	{
		SpawnBlock();
	}
}

bool Board::IsAnimating() const
{
	return animation != Animations::NotAnimating;
}

void Board::PushAnimation( float dt )
{
	assert( animation == Animations::PushColumn );
	if( currentDisplacement > 50.0f )
	{
		animation = Animations::NotAnimating;
		currentDisplacement = 0;
		UpdateBlocks();
	}
	else
	{
		const auto movement = Vec2( 0.0f,-1.0f ) * animationSpeed * dt;
		currentDisplacement += std::abs( movement.y );
		for( Block& block : field[(int) currentColPush] )
		{
			block.LinearShift( movement );
		}
	}
}

void Board::CollapseAnimation( float dt )
{
	assert( animation == Animations::CollapseRow );
	if( currentDisplacement > 50.0f )
	{
		animation = Animations::NotAnimating;
		currentDisplacement = 0;
		SpawnBlock();
		rowsToDelete.clear();
	}
	else
	{
		const auto movement = Vec2( 0.0f,1.0f ) * animationSpeed * dt;
		currentDisplacement += std::abs( movement.y );
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