#include "vec3.h"
#include <cmath>

Vec3::Vec3(){
	x = 0;
	y = 0;
	z = 0;
}
Vec3::Vec3(double xn){
	x = xn;
	y = xn;
	z = xn;
}
Vec3::Vec3(double xn, double yn, double zn){
	x = xn;
	y = yn;
	z = zn;
}

Vec3 Vec3::operator * (const double& xn){
	return Vec3(xn*x, xn*y, xn*z);
}
Vec3 Vec3::operator * (const Vec3& v){
	return Vec3(v.x*x, v.y*y, v.z*z);
}
Vec3 Vec3::operator - (const Vec3& v){
	return Vec3(x - v.x, y - v.y, z - v.z);
}
Vec3 Vec3::operator + (const Vec3& v){
	return Vec3(x + v.x, y + v.y, z + v.z);
}
Vec3& Vec3::operator -= (const Vec3& v){
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
Vec3& Vec3::operator += (const Vec3& v){
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
Vec3& Vec3::operator = (const Vec3& v){
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

double Vec3::length(){
	return sqrt(length2());
}
double Vec3::length2(){
	return dot(*this);
}
double Vec3::dot(const Vec3& v){
	return v.x*x + v.y * y + v.z * z;
}

Vec3& Vec3::normalize(){
	double l2 = length2();
	x/=l2;
	y/=l2;
	z/=l2;
	return *this;
}