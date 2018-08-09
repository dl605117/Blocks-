#pragma once
#include <algorithm>

template <typename T>
class Vec2
{
public:
	Vec2() = default;
	Vec2( T x,T y )
		:
		x( x ),
		y( y )
	{
	}
	Vec2 operator+( const Vec2& rhs ) const
	{
		return Vec2( rhs.x + x,rhs.y + rhs.y );
	}
	Vec2& operator+=( const Vec2& rhs )
	{
		return *this + rhs;
	}
	Vec2 operator-( const Vec2& rhs ) const
	{
		return Vec2( x - rhs.x,y - rhs.y );
	}
	Vec2& operator-=( const Vec2& rhs )
	{
		return *this - rhs;
	}
	Vec2 operator*( T scalar ) const
	{
		return Vec2( x * scalar,y * scalar );
	}
	Vec2& operator*=( T scalar )
	{
		return *this * scalar;
	}
	T GetLengthSq() const
	{
		return x * x + y * y;
	}
	T GetLength() const
	{
		return std::sqrt( GetLengthSq() );
	}
	Vec2& Normalize()
	{
		return *this->GetNormalized();
	}
	Vec2 GetNormalized() const
	{
		const T length = GetLength();
		return Vec2( x / length,y / length );
	}
public:
	T x;
	T y;
};