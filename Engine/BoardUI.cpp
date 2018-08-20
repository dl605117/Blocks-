#include "BoardUI.h"

BoardUI::BoardUI( Board& brd,const std::string& textFileName )
	:
	text( textFileName )
{
	this->brd = &brd ;
}


void BoardUI::Draw( Graphics& gfx ) const
{
	DrawScore( gfx );
	DrawTimer( gfx );
}

void BoardUI::DrawScore( Graphics& gfx ) const
{
	int place = 0;
	for( char digit : std::to_string( brd->GetScore() ) )
	{
		gfx.DrawSprite( 17 * place,0,text,GetNumberRect( digit ),SpriteEffects::Substitute( Colors::White,Colors::Yellow ) );
		place++;
	}
}

RectI BoardUI::GetNumberRect( char digit ) const
{
	Vei2 topLeft( ( digit - ' ' ) * 16,0 );
	return RectI( topLeft,topLeft + Vei2( 17,14 ) );
}

void BoardUI::DrawTimer( Graphics& gfx ) const
{
	float up = float( twoPi / 4 );
	float endAngle = float( ( brd->GetTimer() / Board::maxTimer ) * twoPi );
	endAngle = endAngle < up ? up - endAngle : (float) twoPi - ( endAngle - up );
	gfx.DrawCircle( timerCenterPos,timerOuterRadius,timerColor,CircleEffects::SectorFromCenter( endAngle,float( twoPi / 4 ) ) );
	gfx.DrawCircle( timerCenterPos,timerInnerRadius,Colors::Black,CircleEffects::SectorFromCenter( endAngle,float( twoPi / 4 ) ) );
}