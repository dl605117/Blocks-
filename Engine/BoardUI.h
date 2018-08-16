#pragma once
#include "Board.h"
#include "SpriteEffects.h"

class BoardUI
{
public:
	BoardUI( Board& brd,const std::string& textFileName );
	void Draw( Graphics& gfx );
private:
	void DrawScore( Graphics& gfx );
	RectI GetNumberRect( char digit ) const;
private:
	Board* brd;
	Surface text;
};