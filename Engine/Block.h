#pragma once
#include "Rect.h"
#include "Graphics.h"

class Block
{
public:
	Block( const RectI& block,Color color );
	void Draw( Graphics& gfx );
	void Shift( const Vei2& delta_loc );
public:
	RectI block;
	Color color;
};