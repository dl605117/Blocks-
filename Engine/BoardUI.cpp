#include "BoardUI.h"

BoardUI::BoardUI( Board& brd,const std::string& textFileName )
	:
	text( textFileName )
{
	this->brd = &brd ;
}


void BoardUI::Draw( Graphics& gfx )
{
	DrawScore( gfx );
}

void BoardUI::DrawScore( Graphics& gfx )
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