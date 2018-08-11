#pragma once
#include <algorithm>

template <typename T>
class Vec2_
{
public:
	Vec2_() = default;
	Vec2_( T x,T y )
		:
		x( x ),
		y( y )
	{
	}
	Vec2_ operator+( const Vec2_& rhs ) const
	{
		return Vec2_( rhs.x + x,rhs.y + rhs.y );
	}
	Vec2_& operator+=( const Vec2_& rhs )
	{
		return *this + rhs;
	}
	Vec2_ operator-( const Vec2_& rhs ) const
	{
		return Vec2_( x - rhs.x,y - rhs.y );
	}
	Vec2_& operator-=( const Vec2_& rhs )
	{
		return *this - rhs;
	}
	Vec2_ operator*( T scalar ) const
	{
		return Vec2_( x * scalar,y * scalar );
	}
	Vec2_& operator*=( T scalar )
	{
		return *this * scalar;
	}
	Vec2_ operator/( T scalar ) const
	{
		return Vec2_( T( x / scalar ),T( y / scalar ) );
	}
	Vec2_& operator/=( T scalar )
	{
		return *this / scalar;
	}
	T GetLengthSq() const
	{
		return x * x + y * y;
	}
	T GetLength() const
	{
		return std::sqrt( GetLengthSq() );
	}
	Vec2_& Normalize()
	{
		return *this->GetNormalized();
	}
	Vec2_ GetNormalized() const
	{
		const T length = GetLength();
		return Vec2_( x / length,y / length );
	}
public:
	T x;
	T y;
};

typedef Vec2_<int> Vei2;
typedef Vec2_<float> Vec2;