#pragma once
#include "Rect.h"
#include "Graphics.h"

class Block
{
public:
	Block( const RectF& block,Color color );
	void Draw( Graphics& gfx );
	void LinearShift( const Vec2& delta_loc );
	void SetLoc( const Vec2& new_loc );
public:
	RectF block;
	Color color;
};