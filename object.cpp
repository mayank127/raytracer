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

vector<double> Sphere::intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection) {
	vector<double> points;
	double a, b, c;
	a = rayDirection.length2();
	b = 2 * rayDirection.dot(rayOrigin - center);
	c = (rayOrigin - center).length2() - radius*radius;
	double discriminant = b*b - 4*a*c;
	if (discriminant < 0) return points;
	else {
		discriminant = sqrt(discriminant);
		double t1 = ((-1 * b) + discriminant) / (2 * a);
		double t2 = ((-1 * b) - discriminant) / (2 * a);
		points.push_back(t1);
		points.push_back(t2);
	}
	return points;
}
Vec3 Sphere::getNormal(const Vec3 point){
	return ((point - center).normalize());
}
/*********************************************************************************************************************/

// Cylinder Object
/*********************************************************************************************************************/
Cylinder::Cylinder(Vec3 upVector, double radius, double height, Vec3 surfaceColor, double transparency, Type objectType)
	:Object(surfaceColor, transparency, objectType) {
	this->upVector = upVector;
	this->radius = radius;
	this->height = height;
}

// source : http://www.mathworks.com/matlabcentral/newsreader/view_thread/32952
vector<double> Cylinder::intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection) {

	/*double a = (rayDirection.x*rayDirection.x) + (rayDirection.z * rayDirection.z);
	double b = ((rayOrigin.x - center.x) * rayDirection.x) + ((rayOrigin.z - center.z) * rayDirection.z);
	double c = sqr(rayOrigin.x - center.x) + sqr(rayOrigin.z - center.z) - sqr(radius);

	double discriminant = b*b - a*c;
	int hit = 0, n = 0, inside = 0;

	vector<double> tHit(4,0), sHit(4,0);

	if (discriminant > 0)
		double t1, t2, disc_root;
	    disc_root = sqrt(discriminant);
	    if (abs(a) < 0){
	    	t1 = ((-1 * b) - disc_root) * 1e21;
	        t2 = ((-1 * B) + disc_root) * 1e21;
	    }
	    else {
	    	t1 = ((-1 * b) - disc_root) / a;
	        t2 = ((-1 * B) + disc_root) / a;
	    }

	    double uplim = height + center.y;
	    double lowlim = center.y;
	    double yHit = rayOrigin.y + (rayDirection.y * t1);

	    if (t1 > 0 && yHit <= uplim && yHit>=lowlim) {
	    	tHit[n] = t1;
	        sHit[n] = 0;
	        n++;
	    }

	    yHit = rayOrigin.y + (rayDirection.y * t2)

	    if (t2 > 0 && yHit <= uplim && yHit>=lowlim) {
	    	tHit[n] = t2;
	        sHit[n] = 0;
	        n++;
	    }
	}

	double tb;
	if (abs(rayDirection.y < 0) 
		tb = 1e21;
	else 
		tb = (center.y - rayOrigin.y) / rayDirection.y;
	if (tb >0 && (sqr(rayOrigin.x + (rayDirection.x * tb) - center.x) + sqr(rayOrigin.z + (rayDirection.z * tb) - center.z)) < sqr(radius)) {
		tHit[n] = tb;
	    sHit[n] = 1;
	    n++;
	}
	    
	double tc;
	if (abs(rayDirection.y < 0) 
		tc = 1e21;
	else 
		tc = (height + center.y - rayOrigin.y) / rayDirection.y;
	if (tb >0 && (sqr(rayOrigin.x + (rayDirection.x * tc) - center.x) + sqr(rayOrigin.z + (rayDirection.z * tc) - center.z)) < sqr(radius)) {
		tHit[n] = tc;
	    sHit[n] = 2;
	    n++;
	}

	double tnear, tfar, inside;
	if (n==0) {
		tnear=-1;
		return points;
	}

	if (n==1) {
		double inside = 1;
	    t = (tHit.*(tHit>eps));
	    ind = find(t==min(t));
	    tnear = t(ind);
	    sHit = sHit(ind);
	    hit = 1;
	}
	    
	else {
		if (tHit[0] > tHit[1]) {
			tnear = tHit[1];
	        tfar = tHit[0];
	        double t = sHit[0];
	        sHit[0] = sHit[1];
	        sHit[2] = t;
		}
	    else {
	    	tnear=tHit[0];
	        tfar=tHit[1];
	    }
	    hit = 1;
	}
	    
	Vec3 newIP = rayOrigin + (rayDirection * tnear);
	if (sHit[0] == 0) {
		normal = [newIP(1)-BC(1), 0, newIP(3)-BC(3)];
	    if any(normal), normal=normal/norm(normal)
	}
	else if (sHit[0] == 1),
	    normal = [0,-1,0]; % base
	else,
	    normal = [0,1,0]; % cap
	end

	if inside,
	    normal = -normal;
	end

	newIP
	normal%
	vector<Vec3> points;
	return points;*/
}
Vec3 Cylinder::getNormal(const Vec3 point){}
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

vector<double> Cone::intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection) {
	vector<double> points;
	return points;
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
vector<double> Triangle::intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection) {
	vector<double> points;
	Vec3 e1,e2,h,s,q;
	double a,f,u,v,t;

	e1 = p2 - p1;
	e2 = p3 - p1;
	h = rayDirection.cross(e2);
	a = e1.dot(h);

	if (a > -0.00001 && a < 0.00001)
		return(points);

	f = 1/a;
	s = rayOrigin - p1;
	u = f * (s.dot(h));

	if (u < 0.0 || u > 1.0)
		return(points);

	q = s.cross(e1);
	v = f * rayDirection.dot(q);

	if (v < 0.0 || u + v > 1.0)
		return(points);


	t = f * e2.dot(q);

	if (t > 0.00001) {
		points.push_back(t);
		return(points);
	}
	else
		return (points);
}
Vec3 Triangle::getNormal(const Vec3 point){

}
/*********************************************************************************************************************/