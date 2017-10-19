#pragma once
#include <iostream>
class myRGBColor
{
public:
	double r, g, b;

	myRGBColor() : r(0), g(0), b(0) {}
	myRGBColor(double c) : r(c), g(c), b(c) {}
	myRGBColor(double rr, double gg, double bb) :
		r(rr), g(gg), b(bb) {}
	myRGBColor(const myRGBColor &rhs) :
		r(rhs.r), g(rhs.g), b(rhs.b) {}

	myRGBColor& operator=(const myRGBColor &rhs);

	myRGBColor operator+(const myRGBColor &rhs) const;
	myRGBColor& operator+=(const myRGBColor &rhs);

	myRGBColor operator*(double d) const;
	myRGBColor& operator*=(double d);

	myRGBColor operator*(const myRGBColor &rhs) const;
	myRGBColor& operator*=(const myRGBColor &rhs);

	myRGBColor operator/(double d) const;
	myRGBColor& operator/=(double d);
	
	myRGBColor RGBPow(double d) const;

};

myRGBColor operator*(double d, const myRGBColor &rhs);

std::ostream &operator<<(std::ostream &os, myRGBColor & color);
