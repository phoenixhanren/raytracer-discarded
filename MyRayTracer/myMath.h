#pragma once
#include <cmath>
#include <cassert>
#include <iostream>

#define M_PI       3.14159265358979323846f
#define INV_PI     0.31830988618379067154f
#define INV_TWOPI  0.15915494309189533577f
#define INV_FOURPI 0.07957747154594766788f
#define KEPSILON 0.0000000000001f

class myVector;
class myPoint;
class myNormal;

class myVector
{
	friend std::ostream& operator<<(std::ostream &os, const myVector& v);
public:
	myVector() : x(0.0), y(0.0), z(0.0) {}
	myVector(double forX, double forY, double forZ) :
		x(forX), y(forY), z(forZ) {}
	myVector(const myVector& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {
		////assert(!HasNaNs());
	}
	explicit myVector(const myPoint& rhs);
	explicit myVector(const myNormal& rhs);

	myVector operator+(const myVector& rhs) const {
		return myVector(x + rhs.x,
			y + rhs.y,
			z + rhs.z);
	}
	myVector &operator+=(const myVector& rhs) {
		//assert(!rhs.HasNaNs());
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	myVector operator-(const myVector& rhs) const {
		//assert(!rhs.HasNaNs());
		return myVector(x - rhs.x,
			y - rhs.y,
			z - rhs.z);
	}
	myVector &operator-=(const myVector& rhs) {
		//assert(!rhs.HasNaNs());
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	myVector operator*(double d) const {
		return myVector(d * x, d * y, d * z);
	}
	myVector &operator*=(double d) {
		x *= d;
		y *= d;
		z *= d;
		return *this;
	}

	myVector operator/(double d) const {
		////assert(!(d == 0.0));
		return myVector(x / d, y / d, z / d);
	}
	myVector &operator/=(double d) {
		////assert(!(d == 0.0));
		x /= d;
		y /= d;
		z /= d;
		return *this;
	}

	myVector &operator=(const myVector &rhs) {
		//assert(!rhs.HasNaNs());
		if (this != &rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
		}
		return *this;
	}
	
	double lengthSquared() const{
		return x * x + y * y + z * z;
	}

	double length() const{
		return sqrtl(lengthSquared());
	}

	double operator[](int i) const {
		//assert(!(i >= 0 && i <= 2));
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			break;
		}
	}

	double &operator[](int i) {
		//assert(!(i >= 0 && i <= 2));
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			break;
		}
	}

	bool operator==(const myVector& rhs) const {
		//assert(!rhs.HasNaNs());
		return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
	}
	bool operator!=(const myVector& rhs) const {
		return !(*this == rhs);
	}


	bool HasNaNs() const {
		return std::isnan(x) || std::isnan(y) || std::isnan(z);
	}
	double x, y, z;
};
class myPoint
{
	friend std::ostream& operator<<(std::ostream &os, const myPoint &p);
public:
	//constructors
	myPoint() : x(0.0), y(0.0), z(0.0) {}
	myPoint(double forX, double forY, double forZ) :
		x(forX), y(forY), z(forZ) {
		//assert(!HasNaNs());
	}
	myPoint(const myPoint& rhs) :
		x(rhs.x), y(rhs.y), z(rhs.z) {
		//assert(!HasNaNs());
	}

	explicit myPoint(const myVector& rhs) :
		x(rhs.x), y(rhs.y), z(rhs.z) {

	}

	//operators
	myPoint &operator=(const myPoint& rhsPoint) {
		//assert(!rhsPoint.HasNaNs());
		if (this != &rhsPoint)
		{
			this->x = rhsPoint.x;
			this->y = rhsPoint.y;
			this->z = rhsPoint.z;
		}
		return *this;
	}
	myVector operator-(const myPoint& rhsPoint) const {
		//assert(!rhsPoint.HasNaNs());
		return myVector(this->x - rhsPoint.x,
			this->y - rhsPoint.y,
			this->z - rhsPoint.z);
	}
	myPoint operator-(const myVector& rhsVector) const {
		//assert(!rhsVector.HasNaNs());
		return myPoint(this->x - rhsVector.x,
			this->y - rhsVector.y,
			this->z - rhsVector.z);
	}
	myPoint operator+(const myVector& rhsVector) const {
		//assert(!rhsVector.HasNaNs());
		return myPoint(this->x + rhsVector.x,
			this->y + rhsVector.y,
			this->z + rhsVector.z);
	}
	myPoint &operator+=(const myPoint& rhsPoint) {
		//assert(!rhsPoint.HasNaNs());
		this->x += rhsPoint.x;
		this->y += rhsPoint.y;
		this->z += rhsPoint.z;
		return *this;
	}
	myPoint &operator+=(const myVector& rhsVector) {
		//assert(!rhsVector.HasNaNs());
		this->x += rhsVector.x;
		this->y += rhsVector.y;
		this->z += rhsVector.z;
		return *this;
	}
	myPoint &operator-=(const myVector& rhsVector) {
		//assert(!rhsVector.HasNaNs());
		this->x -= rhsVector.x;
		this->y -= rhsVector.y;
		this->z -= rhsVector.z;
		return *this;
	}
	myPoint operator*(double f) const {
		return myPoint(f * this->x,
			f * this->y,
			f * this->z);
	}
	myPoint &operator*=(double f) {
		this->x *= f;
		this->y *= f;
		this->z *= f;
		return *this;
	}
	myPoint operator/(double f) const {
		//assert(!(f == 0.0));
		return myPoint(this->x / f,
			this->y / f,
			this->z / f);
	}
	myPoint &operator/=(double f) {
		//assert(!(f == 0.0));
		this->x /= f;
		this->y /= f;
		this->z /= f;
		return *this;
	}
	double operator[](int i) const {
		//assert(i >= 0 && i <= 2);
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			break;
		}
	}
	double &operator[](int i) {
		//assert(i >= 0 && i <= 2);
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			break;
		}
	}

	bool operator==(const myPoint& rhs) const {
		//assert(!rhs.HasNaNs());
		return (this->x == rhs.x &&
			this->y == rhs.y &&
			this->z == rhs.z);
	}
	bool operator!=(const myPoint& rhs) const {
		//assert(!rhs.HasNaNs());
		return !(*this == rhs);
	}


	//
	bool HasNaNs() const {
		return std::isnan(this->x) || std::isnan(this->y) || std::isnan(this->z);
	}

	//public data
	double x, y, z;
};
class myNormal
{
	friend std::ostream& operator<<(std::ostream &os, const myNormal &v);
public:
	myNormal() : x(0.0), y(0.0), z(0.0) {}
	myNormal(double forX, double forY, double forZ) :
		x(forX), y(forY), z(forZ) {
		//assert(!HasNaNs());
	}
	myNormal(const myNormal& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {
		//assert(!HasNaNs());
	}
	explicit myNormal(const myVector& rhs) :
		x(rhs.x), y(rhs.y), z(rhs.z) {
		//assert(!HasNaNs());
	}

	myNormal operator+(const myNormal& rhs) const {
		//assert(!rhs.HasNaNs());
		return myNormal(x + rhs.x,
			y + rhs.y,
			z + rhs.z);
	}
	myNormal &operator+=(const myNormal& rhs) {
		//assert(!rhs.HasNaNs());
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}
	
	myNormal operator-() const {
		return myNormal(-x, -y, -z);
	}

	myNormal operator-(const myNormal& rhs) const {
		//assert(!rhs.HasNaNs());
		return myNormal(x - rhs.x,
			y - rhs.y,
			z - rhs.z);
	}
	myNormal &operator-=(const myNormal& rhs) {
		//assert(!rhs.HasNaNs());
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	myNormal operator/(double d) const {
		//assert(!(d == 0.0));
		return myNormal(x / d, y / d, z / d);
	}
	myNormal &operator/=(double d) {
		//assert(!(d == 0.0));
		x /= d;
		y /= d;
		z /= d;
		return *this;
	}

	myNormal operator*(double d) const {
		return myNormal(x * d, y * d, z * d);
	}
	myNormal &operator*=(double d) {
		x *= d;
		y *= d;
		z *= d;
		return *this;
	}

	myNormal &operator=(const myNormal& rhs) {
		//assert(!rhs.HasNaNs());
		if (this != &rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
		}
		return *this;
	}
	double lengthSquared() const {
		return x * x + y * y + z * z;
	}

	double length() const {
		return sqrtl(lengthSquared());
	}

	double operator[](int i) const {
		//assert(!(i >= 0 && i <= 2));
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			break;
		}
	}
	double &operator[](int i) {
		//assert(!(i >= 0 && i <= 2));
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			break;
		}
	}

	bool operator==(const myNormal& rhs) const {
		//assert(!(HasNaNs() || rhs.HasNaNs()));
		return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
	}
	bool operator!=(const myNormal& rhs) const {
		return !(*this == rhs);
	}

	bool HasNaNs() const {
		return std::isnan(x) || std::isnan(y) || std::isnan(z);
	}

	double x, y, z;
};

inline myVector::myVector(const myPoint& rhs) : x(rhs.x), y(rhs.y), z(rhs.z){
	//assert(!HasNaNs());
}
inline myVector::myVector(const myNormal& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {
	//assert(!HasNaNs());
}

inline myVector operator*(double d, const myVector& v) { return v * d; }
inline myNormal operator*(double d, const myNormal& v) { return v * d; }
inline myVector operator-(const myVector& v) {
	return myVector() - v;
}

inline myVector normalize(const myVector& v) {
	double temp = v.length();
	////assert(!(temp == 0.0));
	return v / temp;
}
inline myNormal noralize(const myNormal& v) {
	//std::cout << v << std::endl;
	//std::cout << v.length() << std::endl;
	double temp = v.length();
	////assert(!temp == 0.0);
	return v / temp;
}

inline double distance(const myPoint& start, const myPoint& end) {
	return myVector(end - start).length();
}

inline double dot(const myVector& lhs, const myVector& rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
inline double dot(const myNormal& lhs, const myNormal& rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
inline double dot(const myNormal& lhs, const myVector& rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
inline double dot(const myVector& lhs, const myNormal& rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

inline myVector cross(const myVector& lhs, const myVector& rhs) {
	return myVector(lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x);
}
inline myVector cross(const myVector& lhs, const myNormal& rhs) {
	return myVector(lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x);
}
inline myVector cross(const myNormal& lhs, const myVector& rhs) {
	return myVector(lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x);
}

class myRay
{
	friend std::ostream& operator<<(std::ostream &os, const myRay& r);
public:
	myRay() : tMin(0.0), tMax(INFINITY) {}
	myRay(const myPoint& oo, const myVector& mdir,
		double ttMin = 0, double ttMax = INFINITY) :
		o(oo), dir(mdir), tMin(ttMin), tMax(ttMax) {
		//assert(!HasNaNs());
	}
	myRay(const myRay& r) :
		o(r.o), dir(r.dir), tMin(r.tMin), tMax(r.tMax) {
		//assert(!HasNaNs());
	}

	myRay &operator=(const myRay& rhs) {
		//assert(!rhs.HasNaNs());
		if (this != &rhs)
		{
			o = rhs.o;
			dir = rhs.dir;
			tMin = rhs.tMin;
			tMax = rhs.tMax;
		}
		return *this;
	}

	myPoint operator()(double t) const{
		return o + t * dir;
	}

	bool HasNaNs() const{
		return o.HasNaNs() || dir.HasNaNs() || isnan(tMin) || isnan(tMax);
	}

	myPoint o;
	myVector dir;
	double tMin, tMax;
};


inline std::ostream& operator<<(std::ostream &os, const myVector& v)
{
	os << "MyVector : (" << v.x << ", " << v.y << ", " << v.z << ")\n";
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const myPoint& p)
{
	os << "MyPoint : (" << p.x << ", " << p.y << ", " << p.z << ")\n";
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const myNormal& v) 
{
	os << "MyNormal : (" << v.x << ", " << v.y << ", " << v.z << ")\n";
	return os;
}

inline std::ostream& operator<<(std::ostream &os, const myRay& r) 
{
	os << "myRay : \n\torgin:" << r.o << "\n\tdir:" << r.dir;
	return os;
}

inline void swap(double &a, double &b)
{
	double temp = a;
	a = b;
	b = temp;
	return;
}

inline bool Quadratic(double a, double b, double c, double &tMin, double &tMax)
{
	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0.0)
		return false;

	double rootDiscriminant = sqrtl(discriminant);
	tMin = (b * (-1) - rootDiscriminant) * 0.5 / a;
	tMax = (b * (-1) + rootDiscriminant) * 0.5 / a;
	if (tMin > tMax)
		swap(tMin, tMax);
	return true;
}

inline double min(double lhs, double rhs) {
	if (lhs < rhs)
		return lhs;
	return rhs;
}

inline double max(double lhs, double rhs) {
	if (lhs > rhs)
		return lhs;
	return rhs;
}

class myMatrix
{
public:
	myMatrix() :
		a11(1), a12(0), a13(0), a14(0),
		a21(0), a22(1), a23(0), a24(0),
		a31(0), a32(0), a33(1), a34(0),
		a41(0), a42(0), a43(0), a44(1) {}

	myMatrix(double a, double b, double c, char flag) : myMatrix() {
		if (flag == 't')
		{
			a14 = a;
			a24 = b;
			a34 = c;
		}
		else if (flag == 's')
		{
			a11 = a;
			a22 = b;
			a33 = c;
		}
	

	}

	/**
	 * \brief 
	 * \param vec 
	 */
	void transform(myVector& vec) {
		double _a11 = a11 * vec.x + a12 * vec.y + a13 * vec.z + a14 * 1;
		double _a21 = a21 * vec.x + a22 * vec.y + a23 * vec.z + a24 * 1;
		double _a31 = a31 * vec.x + a32 * vec.y + a33 * vec.z + a34 * 1;
		double _a41 = a41 * vec.x + a42 * vec.y + a43 * vec.z + a44 * 1;
		vec.x = (_a11 / _a41);
		vec.y = (_a21 / _a41);
		vec.z = (_a31 / _a41);
	}

	void transform(myPoint& vec) {
		//std::cout << vec;
		//std::cout << a14 << std::endl;
		double _a11 = a11 * vec.x + a12 * vec.y + a13 * vec.z + a14 * 1;
		double _a21 = a21 * vec.x + a22 * vec.y + a23 * vec.z + a24 * 1;
		double _a31 = a31 * vec.x + a32 * vec.y + a33 * vec.z + a34 * 1;
		double _a41 = a41 * vec.x + a42 * vec.y + a43 * vec.z + a44 * 1;
		//std::cout << _a11 << std::endl;
		vec.x = (_a11 / _a41);
		//std::cout << vec.x << std::endl;
		vec.y = (_a21 / _a41);
		vec.z = (_a31 / _a41);
	}

private:
	double a11, a12, a13, a14;
	double a21, a22, a23, a24;
	double a31, a32, a33, a34;
	double a41, a42, a43, a44;
};