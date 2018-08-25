#include "BoardUI.h"

BoardUI::BoardUI( Board& brd,const std::string& textFileName )
	:
	text( textFileName ),
	boardWidth( brd.GetWidth() ),
	boardHeight( brd.GetHeight() )
{
	Vei2 boardPos = brd.GetPos();
	borderPos = boardPos - 
		Vei2( borderRectWidth + borderPadding,borderRectWidth + borderPadding + timerOuterRadius * 2);
	this->brd = &brd;
	timerCenterPos = borderPos + Vei2( borderWidth + borderPadding,borderRectWidth )
		+ Vei2( -timerOuterRadius,timerOuterRadius );
}

void BoardUI::Draw( Graphics& gfx ) const
{
	DrawScore( gfx );
	DrawTimer( gfx );
	DrawBorder( gfx );
}

void BoardUI::DrawScore( Graphics& gfx ) const
{
	int place = 0;
	for( char digit : std::to_string( brd->GetScore() ) )
	{
		gfx.DrawSprite( borderPos.x + borderRectWidth + 17 * place,
			borderPos.y + borderRectWidth,
			text,GetNumberRect( digit ),SpriteEffects::Substitute( Colors::White,Colors::Yellow ) );
		place++;
	}
}

RectI BoardUI::GetNumberRect( char digit ) const
{
	Vei2 topLeft( ( digit - ' ' ) * 16,0 );
	return RectI( topLeft,topLeft + Vei2( 16,28 ) );
}

void BoardUI::DrawTimer( Graphics& gfx ) const
{
	float up = float( twoPi / 4 );
	float endAngle = float( ( brd->GetTimer() / Board::maxTimer ) * twoPi );
	endAngle = endAngle < up ? up - endAngle : (float) twoPi - ( endAngle - up );
	gfx.DrawCircle( timerCenterPos,timerOuterRadius,timerColor,CircleEffects::SectorFromCenter( endAngle,float( twoPi / 4 ) ) );
	gfx.DrawCircle( timerCenterPos,timerInnerRadius,Colors::Black,CircleEffects::SectorFromCenter( endAngle,float( twoPi / 4 ) ) );
}

void BoardUI::DrawBorder( Graphics& gfx ) const
{
	const int doubleBorderPadding = borderPadding * 2;
	// top
	gfx.DrawRect( borderPos,borderWidth + doubleBorderPadding,borderRectWidth );
	// left
	gfx.DrawRect( borderPos + Vei2( 0,borderRectWidth),
		borderRectWidth,borderHeight + doubleBorderPadding );
	// right
	gfx.DrawRect( borderPos + Vei2( borderWidth - borderRectWidth + doubleBorderPadding,borderRectWidth ),
		borderRectWidth,borderHeight + doubleBorderPadding );
	// bottom
	gfx.DrawRect( borderPos + Vei2( 0,borderHeight + borderRectWidth + doubleBorderPadding ),
		borderWidth + borderPadding * 2,borderRectWidth );
}