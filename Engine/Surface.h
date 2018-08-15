#pragma once
#include "Colors.h"
#include <string>
#include <memory>

class Surface
{
public:
	Surface( const std::string& filename );
	void PutPixel( int x,int y,Color color );
	Color& GetPixel( int x,int y ) const;
	int GetWidth() const;
	int GetHeight() const;
private:
	Color* pColor = nullptr;
	int width;
	int height;

};