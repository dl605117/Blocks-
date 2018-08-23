#pragma once
#include "Graphics.h"

struct SpriteEffects
{
public:
	class NoEffect
	{
	public:
		void operator()( Color c,int x,int y,Graphics& gfx)
		{
			gfx.PutPixel( x,y,c );
		}
	};
	
	class Chroma
	{
	public:
		Chroma( Color chroma )
			:
			chroma( chroma )
		{
		}
		void operator()( Color c,int x,int y,Graphics& gfx )
		{
			if( c != chroma )
			{
				gfx.PutPixel( x,y,c );
			}
		}
		Color chroma;
	};

	class Substitute
	{
	public:
		Substitute( Color chroma,Color substitute )
			:
			chroma( chroma ),
			substitute( substitute )
		{
		}
		void operator()( Color c,int x,int y,Graphics& gfx )
		{
			if( c != chroma )
			{
				gfx.PutPixel( x,y,substitute );
			}
		}
		Color chroma;
		Color substitute;
	};

	class Ghost
	{
	public:
		Ghost( Color chroma )
			:
			chroma( chroma )
		{
		}
		void operator()( Color c,int x,int y,Graphics& gfx )
		{
			if( c != chroma )
			{
				const Color backgroundColor = gfx.GetPixel( x,y );
				const Color mixed = Color(
					( backgroundColor.GetR() + c.GetR() ) / 2,
					( backgroundColor.GetG() + c.GetG() ) / 2,
					( backgroundColor.GetB() + c.GetB() ) / 2
				);
				gfx.PutPixel( x,y,mixed );
			}
		}
		Color chroma;
	};
};