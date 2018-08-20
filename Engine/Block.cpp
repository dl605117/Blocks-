#include "Block.h"

Block::Block( const RectF& block,Color color )
	:
	block( block ),
	color( color )
{
}

void Block::Draw( Graphics& gfx )
{
	gfx.DrawRect( block,color );
}

void Block::LinearShift( const Vec2& delta_loc )
{
	block.left += delta_loc.x;
	block.right += delta_loc.x;
	block.top += delta_loc.y;
	block.bottom += delta_loc.y;
}

void Block::SetLoc( const Vec2& new_loc )
{
	const float width = block.GetWidth();
	const float height = block.GetHeight();
	block.left = new_loc.x;
	block.top = new_loc.y;
	block.right = block.left + width;
	block.bottom = block.top + height;
}