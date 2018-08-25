#pragma once
#include "Board.h"
#include "SpriteEffects.h"
#include "CircleEffects.h"
#include "Graphics.h"

class BoardUI
{
public:
	BoardUI( Board& brd,const std::string& textFileName );
	void Draw( Graphics& gfx ) const;
private:
	void DrawScore( Graphics& gfx ) const;
	RectI GetNumberRect( char digit ) const;
	void DrawTimer( Graphics& gfx ) const;
	void DrawBorder( Graphics& gfx ) const;
private:
	static constexpr int timerOuterRadius = 20;
	static constexpr int timerInnerRadius = 15;
	static constexpr Color timerColor = Colors::Yellow;
	static constexpr int borderPadding = 10;
	static constexpr int borderRectWidth = 10;
	Vei2 borderPos;
	int boardWidth;
	int boardHeight;
	int borderHeight = boardHeight + timerOuterRadius * 2;
	int borderWidth = boardWidth + borderRectWidth * 2;
	const double twoPi = 2 * std::acos( -1 );
	Vei2 timerCenterPos;
	Board* brd;
	Surface text;
};