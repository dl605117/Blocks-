#include "Board.h"

Board::Board()
	:
	rng( std::random_device()() )
{
}

void Board::PushColumn( Column col )
{
	assert( field[0].size() == 1 );
	field[0][0].Shift( Vei2( 100 * ( col - 1 ),0 ) );
	field[1 + col].emplace_back( field[0][0] );
	field[0].clear();
	//field[1 + col].emplace_back( std::move( field[0][0] ) );
	for( Block& block : field[1 + col] )
	{
		block.Shift( Vei2( 0,-50 ) );
	}
}

void Board::SpawnBlock()
{
	assert( field[0].size() == 0 );
	std::uniform_int_distribution<int> colorDist( 0,2 );
	field[0].emplace_back(
		Block( RectI( Vei2( Graphics::ScreenWidth - blockWidth,
			Graphics::ScreenHeight + 500 - blockHeight ) / 2,
			blockWidth,blockHeight),
			blockColors[colorDist( rng ) ] ) );
}

void Board::Draw( Graphics& gfx )
{
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