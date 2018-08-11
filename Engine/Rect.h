#pragma once
#include "Vec2.h"
#include "Colors.h"

template<typename T>
class Rect
{
public:
	Rect() = default;
	Rect( T left,T top,T right,T bottom )
		:
		left( left ),
		right( right ),
		top( top ),
		bottom( bottom )
	{
	}
	Rect( const Vec2_<T>& topLeft,const Vec2_<T>& bottomRight )
		:
		Rect( topLeft.x, topLeft.y, bottomRight.x, bottomRight.y )
	{
	}
	Rect( const Vec2_<T>& topLeft,T width,T height )
		:
		Rect( topLeft.x, topLeft.y, topLeft.x + width, topLeft.y + height )
	{
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
};

typedef Rect<int> RectI;
typedef Rect<float> RectF;