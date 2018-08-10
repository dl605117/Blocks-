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
	choiceBlock->Shift( Vei2( 100 * ( col - 1 ),0 ) );
	field[col].push_back( *choiceBlock );
	for( Block& block : field[col] )
	{
		block.Shift( Vei2( 0,-50 ) );
	}
}

void Board::SpawnBlock()
{
	std::uniform_int_distribution<int> colorDist( 0,2 );
	choiceBlock = std::make_unique<Block>(
		RectI( Vei2( Graphics::ScreenWidth - blockWidth,
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
			return true;
		}
	}
	return false;
}

void Board::UpdateCollapse()
{
	int minRight = std::min(
		int( field[0].size() ),
		int( field[1].size() ) );
	int minRows = std::min(
		int(field[2].size()),minRight );

	for( int row = 0; row < minRows; row++ )
	{
		const Color matchColor = field[0][field[0].size() - 1 - row].color;
		if( field[1][field[1].size() - 1 - row].color == matchColor
			&& field[2][field[2].size() - 1 - row].color == matchColor )
		{
			for( std::vector<Block>& col : field )
			{
				col.erase( col.end() - 1 - row );
			}
			for( std::vector<Block>& col : field )
			{
				for( int i = col.size() - 1 - row; i >= 0; i-- )
				{
					col[i].Shift( Vei2( 0,50 ) );
				}
			}
			minRows--;
			row--;
		}
	}
}