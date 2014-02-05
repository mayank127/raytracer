#include <iostream>
#include <vector>
#include <cmath>
#include "object.h"
using namespace std;


// Object
/*********************************************************************************************************************/

Object::Object(Vec3 surfaceColor, double transparency, Type objectType){
	this->surfaceColor = surfaceColor;
	this->transparency = transparency;
	this->objectType = objectType;
}

/*********************************************************************************************************************/
// Sphere Object
/*********************************************************************************************************************/
Sphere::Sphere(Vec3 center, double radius, Vec3 surfaceColor, double transparency, Type objectType)
	:Object(surfaceColor, transparency, objectType) {
	this->center = center;
	this->radius = radius;
}

double Sphere::intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection) {
	vector<double> points;
	double a, b, c;
	a = rayDirection.length2();
	b = 2 * rayDirection.dot(rayOrigin - center);
	c = (rayOrigin - center).length2() - radius*radius;
	double discriminant = b*b - 4*a*c;
	if (discriminant < 0) return -1;
	else {
		discriminant = sqrt(discriminant);
		double t1 = ((-1 * b) + discriminant) / (2 * a);
		double t2 = ((-1 * b) - discriminant) / (2 * a);
		points.push_back(t1);
		points.push_back(t2);
	}
	double minT = INFINITY;
	for(int i=0;i<points.size();i++){
		if(minT > points[i]) minT = points[i];
	}
	return minT;
}
Vec3 Sphere::getNormal(const Vec3 point){
	return ((point - center).normalize());
}
/*********************************************************************************************************************/

// Cylinder Object
/*********************************************************************************************************************/
Cylinder::Cylinder(Vec3 center, Vec3 upVector, double radius, double height, Vec3 surfaceColor, double transparency, Type objectType)
	:Object(surfaceColor, transparency, objectType) {
	this->center = center;
	this->upVector = upVector.normalize();
	this->radius = radius;
	this->height = height;
}

// source :http://mrl.nyu.edu/~dzorin/cg05/lecture12.pdf
double Cylinder::intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection) {
	vector<double> points;
	Vec3 alpha = upVector * rayDirection.dot(upVector);
	Vec3 deltaP = (rayOrigin - center);
	Vec3 beta = upVector * deltaP.dot(upVector);
	Vec3 center2 = center + upVector*height;

	double a = (rayDirection - alpha).length2();
	double b = 2 * ((rayDirection - alpha).dot(deltaP - beta));
	double c = (deltaP - beta).length2() - radius*radius;

	double discriminant = b*b - 4*a*c;
	if (discriminant < 0) return -1;
	else {
		discriminant = sqrt(discriminant);
		double t1 = ((-1 * b) + discriminant) / (2 * a);
		double t2 = ((-1 * b) - discriminant) / (2 * a);
		if(t1>=0){
			if(upVector.dot((rayOrigin - center) + rayDirection * t1)>0 && upVector.dot((rayOrigin - center2) + rayDirection * t1)<0)
				points.push_back(t1);
		}
		if(t2>=0)
			if(upVector.dot((rayOrigin - center) + rayDirection * t2)>0 && upVector.dot((rayOrigin - center2) + rayDirection * t2)<0)
				points.push_back(t2);
	}

	float denom = rayDirection.dot(upVector);
	if (denom > 1e-6) {
		Vec3 co = center - rayOrigin;
		double t3 = co.dot(upVector) / denom;
		if(t3 > 0 && (rayDirection * t3 - co).length2() <= radius*radius)
			points.push_back(t3);
	} else if (denom < 1e-6) {
		Vec3 co2 = center2 - rayOrigin;
		double t4 = co2.dot(upVector) / denom;
		if(t4 > 0 && (rayDirection * t4 - co2).length2() <= radius*radius)
			points.push_back(t4);
	}

	double minT = INFINITY;
	bool flag = false;
	for(int i=0;i<points.size();i++){
		if(minT > points[i]) {
			minT = points[i];
			flag = true;
		}
	}
	if(flag)
		return minT;
	else
		return -1;
}
Vec3 Cylinder::getNormal(const Vec3 point){
	Vec3 co = point - center;
	Vec3 co2 = co - upVector*height;
	if(co.length2() <= radius * radius)
		return (upVector.normalize());
	if(co2.length2() <= radius * radius)
		return upVector.normalize();
	Vec3 normal = co - co.project(upVector);
	return normal.normalize();
}
/*********************************************************************************************************************/

// Cone Object
/*********************************************************************************************************************/
Cone::Cone(Vec3 upVector, Vec3 inclineVector, double radius, double height, Vec3 surfaceColor, double transparency, Type objectType)
	:Object(surfaceColor, transparency, objectType) {
	this->upVector = upVector;
	this->inclineVector = inclineVector;
	this->radius = radius;
	this->height = height;
}

double Cone::intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection) {
	double point = -1;
	return point;
}
Vec3 Cone::getNormal(const Vec3 point){

}
/*********************************************************************************************************************/

// Triangle Object
/*********************************************************************************************************************/
Triangle::Triangle(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 surfaceColor, double transparency, Type objectType)
	:Object(surfaceColor, transparency, objectType) {
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
}


// Source : http://www.lighthouse3d.com/tutorials/maths/ray-triangle-intersection/
double Triangle::intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection) {
	vector<double> points;
	Vec3 e1,e2,h,s,q;
	double a,f,u,v,t;

	e1 = p2 - p1;
	e2 = p3 - p1;
	h = rayDirection.cross(e2);
	a = e1.dot(h);

	if (a > -0.00001 && a < 0.00001)
		return(-1);

	f = 1/a;
	s = rayOrigin - p1;
	u = f * (s.dot(h));

	if (u < 0.0 || u > 1.0)
		return(-1);

	q = s.cross(e1);
	v = f * rayDirection.dot(q);

	if (v < 0.0 || u + v > 1.0)
		return(-1);


	t = f * e2.dot(q);

	if (t > 0.00001) {
		return(t);
	}
	else
		return (-1);
}
Vec3 Triangle::getNormal(const Vec3 point){

}
/*********************************************************************************************************************/