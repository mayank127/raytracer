#include <iostream>
#include <vector>
#include <cmath>
#include "object.h"
using namespace std;

// Sphere Object
/*********************************************************************************************************************/
Sphere::Sphere(Vec3 center, double radius) {
	this->center = center;
	this->radius = radius;
}

vector<Vec3> Sphere::intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection) {
	vector<Vec3> points;
	double a, b, c;
	a = rayDirection.length2();
	b = 2 * rayDirection.dot(rayOrigin - center);
	c = (rayOrigin - center).length2() - radius*radius;
	double discriminant = b*b - 4*a*c;
	if (discriminant < 0) return points;
	else if (discriminant==0) {
		double t = (-1 * b)/(2 * a);
		Vec3 p1 = rayOrigin + (rayDirection * t);
		points.push_back(p1);
	}
	else {
		discriminant = sqrt(discriminant);
		double t1 = ((-1 * b) + discriminant) / (2 * a);
		double t2 = ((-1 * b) - discriminant) / (2 * a);
		Vec3 p1 = rayOrigin + (rayDirection * t1);
		Vec3 p2 = rayOrigin + (rayDirection * t2);
		points.push_back(p1);
		points.push_back(p2);
	}
	return points;
}
/*********************************************************************************************************************/

// Cylinder Object
/*********************************************************************************************************************/
Cylinder::Cylinder(Vec3 upVector, double radius, double height) {
	this->upVector = upVector;
	this->radius = radius;
	this->height = height;
}

vector<Vec3> Cylinder::intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection) {
	vector<Vec3> points;
	return points;
}
/*********************************************************************************************************************/

// Cone Object
/*********************************************************************************************************************/
Cone::Cone(Vec3 upVector, Vec3 inclineVector, double radius, double height) {
	this->upVector = upVector;
	this->inclineVector = inclineVector;
	this->radius = radius;
	this->height = height;
}

vector<Vec3> Cone::intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection) {
	vector<Vec3> points;
	return points;
}
/*********************************************************************************************************************/

// Triangle Object
/*********************************************************************************************************************/
Triangle::Triangle(Vec3 p1, Vec3 p2, Vec3 p3) {
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
}

vector<Vec3> Triangle::intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection) {
	vector<Vec3> points;
	return points;
}
/*********************************************************************************************************************/