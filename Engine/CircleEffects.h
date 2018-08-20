#pragma once
#include "Graphics.h"

struct CircleEffects
{
public:
	class Circle
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

	class CircleFromCenter : public Circle
	{
	};

	class Sector
	{
	public:
		Sector( float beginDeg,float endDeg )
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

	class SectorFromCenter : public Sector
	{
	public:
		SectorFromCenter( float beginDeg,float endDeg )
			:
			Sector( beginDeg,endDeg )
		{
		}
	};

	class Ring
	{
	public:
		Ring( int innerRadius )
			:
			innerRadiusSq( innerRadius * innerRadius )
		{
		}
		void operator()( const Vei2& center,int dx,int dy,int radiusSq,Color c,Graphics& gfx )
		{
			const int pythagSq = dy * dy + dx * dx;
			if( pythagSq <= radiusSq && pythagSq >= innerRadiusSq)
			{
				gfx.PutPixel( center.x + dx,center.y + dy,c );
			}
		}
		int innerRadiusSq;
	};

	class RingFromCenter : public Ring
	{
	public:
		RingFromCenter( int innerRadius )
			:
			Ring( innerRadius )
		{
		}
	};

	class RingSector
	{
	public:
		RingSector( float beginDeg,float endDeg,int innerRadius )
			:
			beginDeg( beginDeg ),
			endDeg( endDeg ),
			innerRadiusSq( innerRadius * innerRadius )
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
			const int pythagSq = dy * dy + dx * dx;
			if( opp )
			{
				if( ( angle >= beginDeg || angle < endDeg ) 
					&& pythagSq <= radiusSq && pythagSq >= innerRadiusSq )
				{
					gfx.PutPixel( center.x + dx,center.y + dy,c );
				}
			}
			else if( angle < endDeg && angle >= beginDeg 
				&& pythagSq <= radiusSq && pythagSq >= innerRadiusSq )
			{
				gfx.PutPixel( center.x + dx,center.y + dy,c );
			}
		}
		float beginDeg;
		float endDeg;
		int innerRadiusSq;
		bool opp = false;
		const Vei2 zeroDegrees = Vei2( 1,0 );
		const double twoPi = std::acos( -1 ) * 2;
	};

	class RingSectorFromCenter : public RingSector
	{
	public:
		RingSectorFromCenter( float beginDeg,float endDeg,int innerRadius )
			:
			RingSector( beginDeg,endDeg,innerRadius )
		{
		}
	};
};