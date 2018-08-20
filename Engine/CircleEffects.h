#pragma once
#include "Graphics.h"

struct CircleEffects
{
public:
	class CircleFromCenter
	{
	public:
		void operator()( const Vei2& center,int dx,int dy,int radiusSq,Color c,Graphics& gfx )
		{
			if( dy * dy + dx * dx <= radiusSq )
			{
				gfx.PutPixel( center.x + dx,center.y + dy,c );
			}
		}
	};

	class SectorFromCenter
	{
	public:
		SectorFromCenter( float beginDeg,float endDeg )
			:
			beginDeg( beginDeg ),
			endDeg( endDeg )
		{
			if( beginDeg > endDeg || beginDeg < 0 )
			{
				opp = true;
			}
		}
		void operator()( const Vei2& center,int dx,int dy,int radiusSq,Color c,Graphics& gfx )
		{
			double angle = zeroDegrees.GetAngle( Vei2( dx,-dy ) );
			angle += angle < 0 ? twoPi : 0;
			if( opp )
			{
				if( ( angle >= beginDeg || angle < endDeg ) && dy * dy + dx * dx <= radiusSq )
				{
					gfx.PutPixel( center.x + dx,center.y + dy,c );
				}
			}
			else if( angle < endDeg && angle >= beginDeg && dy * dy + dx * dx <= radiusSq )
			{
				gfx.PutPixel( center.x + dx,center.y + dy,c );
			}
		}
		float beginDeg;
		float endDeg;
		bool opp = false;
		const Vei2 zeroDegrees = Vei2( 1,0 );
		const double twoPi = std::acos( -1 ) * 2;
	};
};