#pragma once
#include "Vec2.h"
#include "Colors.h"

template<typename T>
class Rect
{
public:
	Rect() = default;
	Rect( T left,T top,T right,T bottom,Color color )
		:
		left( left ),
		right( right ),
		top( top ),
		bottom( bottom ),
		color( color )
	{
	}
	Rect( const Vei2& topLeft,const Vei2& bottomRight,Color color )
		:
		Rect( topLeft.x, topLeft.y, bottomRight.x, bottomRight.y, color )
	{
	}
	Rect( const Vei2& topLeft,T width,T height,Color color )
		:
		Rect( topLeft.x, topLeft.y, topLeft.x + width, topLeft.y + height, color )
	{
	}
	void Shift( const Vei2& delta_loc )
	{
		left += delta_loc.x;
		right += delta_loc.x;
		top += delta_loc.y;
		bottom += delta_loc.y;
	}
	T GetWidth() const
	{
		return right - left;
	}
	T GetHeight() const
	{
		return bottom - height;
	}
public:
	T left;
	T right;
	T top;
	T bottom;
	Color color;
};

typedef Rect<int> RectI;