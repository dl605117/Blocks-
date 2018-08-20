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
private:
	static constexpr int timerOuterRadius = 100;
	static constexpr int timerInnerRadius = 80;
	static constexpr Color timerColor = Colors::Yellow;
	const double twoPi = 2 * std::acos( -1 );
	Vei2 timerCenterPos{ Graphics::ScreenWidth - timerOuterRadius,
		timerOuterRadius };
	Board* brd;
	Surface text;
};