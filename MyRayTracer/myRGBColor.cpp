#include "myRGBColor.h"
#include <cmath>

myRGBColor& myRGBColor::operator=(const myRGBColor &rhs)
{
	// TODO: 在此处插入 return 语句
	if (this != &rhs)
	{
		r = rhs.r;
		b = rhs.b;
		g = rhs.g;
	}
	return *this;
}

myRGBColor myRGBColor::operator+(const myRGBColor &rhs) const
{
	return myRGBColor(r + rhs.r,
		g + rhs.g, b + rhs.b);
}

myRGBColor& myRGBColor::operator+=(const myRGBColor &rhs)
{
	// TODO: 在此处插入 return 语句
	r += rhs.r;
	g += rhs.g;
	b += rhs.b;
	return *this;
}

myRGBColor myRGBColor::operator*(double d) const
{
	return myRGBColor(r * d, g * d, b * d);
}

myRGBColor operator*(double d, const myRGBColor &rhs)
{
	return rhs * d;
}

myRGBColor& myRGBColor::operator*=(double d)
{
	// TODO: 在此处插入 return 语句
	r *= d;
	g *= d;
	b *= d;
	return *this;
}

myRGBColor myRGBColor::operator*(const myRGBColor& rhs) const
{
	return myRGBColor(r * rhs.r, g * rhs.g, b * rhs.b);
}

myRGBColor& myRGBColor::operator*=(const myRGBColor& rhs)
{
	// TODO: 在此处插入 return 语句
	r *= rhs.r;
	g *= rhs.g;
	b *= rhs.b;
	return *this;
}

myRGBColor myRGBColor::operator/(double d) const
{
	return myRGBColor(r / d, g / d, b / d);
}

myRGBColor& myRGBColor::operator/=(double d)
{
	// TODO: 在此处插入 return 语句
	r /= d;
	g /= d;
	b /= d;
	return *this;
}

myRGBColor myRGBColor::RGBPow(double d) const
{
	return myRGBColor(pow(r, d), pow(g, d), pow(b, d));
}

std::ostream &operator<<(std::ostream &os, myRGBColor & color)
{
	os << "color: (" << color.r << ", " << color.g << ", " << color.b << ")\n";
	return os;
}