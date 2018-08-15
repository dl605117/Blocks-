#include "Surface.h"
#include "ChiliWin.h"
#include <assert.h>
#include <fstream>

Surface::Surface( const std::string & filename )
{
	std::ifstream file( filename,std::ios::binary );
	assert( file );

	BITMAPFILEHEADER bmpFileHeader;
	file.read( reinterpret_cast<char*>( &bmpFileHeader ),sizeof( bmpFileHeader ) );

	BITMAPINFOHEADER bmpInfoHeader;
	file.read( reinterpret_cast<char*>( &bmpInfoHeader ),sizeof( bmpInfoHeader ) );
	
	assert( bmpInfoHeader.biBitCount == 24 || bmpInfoHeader.biBitCount == 32);
	assert( bmpInfoHeader.biCompression == BI_RGB );

	const bool is32 = bmpInfoHeader.biBitCount == 32;

	width = bmpInfoHeader.biWidth;
	
	int dy = 1;
	int startY = 0;
	int endY = 0;

	if( bmpInfoHeader.biHeight < 0 )
	{
		height = -bmpInfoHeader.biHeight;
		endY = height;
	}
	else
	{
		height = bmpInfoHeader.biHeight;
		dy = -1;
		startY = height - 1;
	}

	pColor = new Color[width * height];

	file.seekg( bmpFileHeader.bfOffBits );
	const int padding = (4 % width * bmpInfoHeader.biBitCount / 4 ) % 4;

	for( int y = startY; y != endY; y += dy )
	{
		for( int x = 0; x < width; x++ )
		{
			PutPixel( x,y,Color( file.get(),file.get(),file.get() ) );
			if( is32 )
			{
				file.get();
			}
		}
		if( !is32 )
		{
			file.seekg( padding,std::ios::cur );
		}
	}
}


void Surface::PutPixel( int x,int y,Color color )
{
	assert( x >= 0 );
	assert( x < width );
	assert( y >= 0 );
	assert( y < height );
	pColor[x + y * width] = color;
}

Color& Surface::GetPixel( int x,int y ) const
{
	assert( x >= 0 );
	assert( x < width );
	assert( y >= 0 );
	assert( y < height );
	return pColor[x + y * width];
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}