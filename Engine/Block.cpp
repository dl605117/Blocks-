#include "Block.h"

Block::Block( const RectI& block,Color color )
	:
	block( block ),
	color( color )
{
}

void Block::Draw( Graphics& gfx )
{
	gfx.DrawRect( block,color );
}

void Block::Shift( const Vei2& delta_loc )
{
	block.left += delta_loc.x;
	block.right += delta_loc.x;
	block.top += delta_loc.y;
	block.bottom += delta_loc.y;
}