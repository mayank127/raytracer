#ifndef VEC3_H
#define VECT_H

class Vec3 {

public:
	double x,y,z;

	Vec3();
	Vec3(double);
	Vec3(double,double,double);


	Vec3 operator * (const double&) const;
	Vec3 operator * (const Vec3&) const;
	Vec3 operator - (const Vec3&) const;
	Vec3 operator + (const Vec3&) const;
	Vec3& operator -= (const Vec3&);
	Vec3& operator += (const Vec3&);
	Vec3& operator = (const Vec3&);

	double length() const;
	double length2() const;
	double dot(const Vec3&) const;

	Vec3& normalize();
};


#endif