#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "vec3.h"
using namespace std;

enum Type {SPECULAR, DIFFUSED}; 

class Object {

public:

	Vec3 surfaceColor;
	double transparency;
	Type objectType;

	virtual vector<Vec3> intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection) = 0;
};

class Sphere : public Object {

public:

	Vec3 center;
	double radius;

	Sphere(Vec3 center, double radius);
	vector<Vec3> intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection);
};

class Cylinder : public Object {

public:

	double radius, height;
	Vec3 upVector;

	Cylinder(Vec3 upVector, double radius, double height);
	vector<Vec3> intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection);
};

class Cone : public Object {

public:

	double radius, height;
	Vec3 upVector, inclineVector;

	Cone(Vec3 upVector, Vec3 inclineVector, double radius, double height);
	vector<Vec3> intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection);
};

class Triangle : public Object {

public:

	Vec3 p1, p2, p3;

	Triangle(Vec3 p1, Vec3 p2, Vec3 p3);
	vector<Vec3> intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection);
};

#endif