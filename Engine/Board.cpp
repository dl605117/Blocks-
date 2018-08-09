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
	for( RectI& block : field[1 + col] )
	{
		block.Shift( Vei2( 0,-50 ) );
	}
}

void Board::SpawnBlock()
{
	assert( field[0].size() == 0 );
	std::uniform_int_distribution<int> colorDist( 0,2 );
	field[0].emplace_back(
		RectI( Vei2( Graphics::ScreenWidth - blockWidth,
			Graphics::ScreenHeight + 500 - blockHeight ) / 2,
			blockWidth,blockHeight,
			blockColors[colorDist( rng ) ] ) );
}

void Board::Draw( Graphics& gfx )
{
	for( std::vector<RectI> col : field )
	{
		for( RectI block : col )
		{
			gfx.DrawRect( block );
		}
	}
}

bool Board::IsOver() const
{
	for( std::vector<RectI> col : field )
	{
		if( col.size() >= maxRows )
		{
			return true;
		}
	}
	return false;
}