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
};