#pragma once
#include "Board.h"
#include "SpriteEffects.h"

class BoardUI
{
public:
	BoardUI( Board& brd,const std::string& textFileName );
	void Draw( Graphics& gfx ) const;
private:
	void DrawScore( Graphics& gfx ) const;
	RectI GetNumberRect( char digit ) const;
	void DrawTimer( Graphics& gfx );
private:
	Board* brd;
	Surface text;
};