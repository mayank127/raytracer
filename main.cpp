#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include "vec3.h"
#include "object.h"
#include "light.h"
#include "matrix.h"
#include <algorithm>
#include <cstdlib>
using namespace std;

#define HEIGHT 480
#define WIDTH 640
#define RECURSION_DEPTH 5
#define TOTAL_SAMPLE 16

Vec3 sendRay(Vec3 rayOrigin, Vec3 rayDirection, int level, vector<Object*> objects, vector<Light> lights){
	double intersectPoint = INFINITY;
	bool doesIntersect = false;
	Object* intersectObject = NULL;
	for(vector<Object*>::iterator it = objects.begin() ; it != objects.end(); ++it) {
		double point = (*it)->intersectionPoints(rayOrigin, rayDirection);
		if(point<0) continue;
		else {
			doesIntersect = true;
			if(intersectPoint > point){
				intersectPoint = point;
				intersectObject = (*it);
			}
		}
	}

	if(!doesIntersect) return Vec3(2);
	Vec3 point = rayOrigin + rayDirection * intersectPoint;
	Vec3 normal = intersectObject->getNormal(point);
	Vec3 finalColor(0);

	bool isIn = false;
	if(normal.dot(rayDirection)>0) {
		normal = normal * -1;
		isIn = true;
	}

	if(intersectObject->objectType == SPECULAR && level < RECURSION_DEPTH) {
		Vec3 reflectionDir = rayDirection - (normal * 2 * rayDirection.dot(normal));
		reflectionDir.normalize();
		double facingratio = -1 * rayDirection.dot(normal);
		double fresneleffect = 0.1 + pow(1 - facingratio, 3) * 0.9;

		Vec3 reflectionColor = sendRay(point + reflectionDir * 0.01 , reflectionDir, level + 1, objects, lights);

		Vec3 refractionColor(0);

		if(intersectObject->transparency > 0){
			double n1 = 1;
			double n2 = intersectObject->transparency;
			double n = isIn ? n2/n1 : n1/n2;
			double c1 = -rayDirection.dot(normal);
			double c2 = 1 - (n*n * (1 - c1*c1));

			if(c2 > 0){
				Vec3 refractionDir = (rayDirection * n) +  (normal * (n*c1 - sqrt(c2)));

				refractionDir.normalize();
				refractionColor = sendRay(point + refractionDir * 0.01, refractionDir, level + 1, objects, lights); 
			}
		}
		finalColor += (reflectionColor * fresneleffect + refractionColor * (1- fresneleffect)) * intersectObject->surfaceColor;

	}

	else{
		for(vector<Light>::iterator light = lights.begin() ; light != lights.end(); ++light) {
			Vec3 pos = light->position;
			Vec3 lightDir = point - pos;
			lightDir.normalize();
			bool shadow = false;
			intersectPoint = INFINITY;
			for(vector<Object*>::iterator it = objects.begin() ; it != objects.end(); ++it){
				double point = (*it)->intersectionPoints(pos, lightDir);
				if(point<0) continue;
				else {
					shadow = true;
					if(intersectPoint > point){
						intersectPoint = point;
						intersectObject = (*it);
					}
				}
			}
			if(point == (pos + lightDir * intersectPoint)) shadow = false;
			if(!shadow) {
				lightDir = lightDir * -1;
				double colorFactor = normal.dot(lightDir);
				if(colorFactor > 0){
					finalColor += intersectObject->surfaceColor * light->colors * colorFactor * intersectObject->phongCoeffs.x * (1/(point - pos).length2());
				}
				if(intersectObject->objectType == SPECULAR){
					Vec3 V = rayOrigin - point;
					V.normalize();
					double shine = normal.dot((V + lightDir).normalize());
					if(shine > 0){
						shine = pow(shine, 50) * intersectObject->phongCoeffs.y * (1/(point - pos).length2());
						finalColor += intersectObject->surfaceColor * light->colors * shine;
					}
				}
			}
		}
	}
	return finalColor;
}

void init(vector<Object*> objects, vector<Light> lights){
	double fov = 30, aspectRatio = WIDTH/(double) HEIGHT;
	double angle = tan((M_PI/2)*fov/180);

	vector<vector<Vec3> > image(WIDTH, vector<Vec3>(HEIGHT, Vec3()));
	for(int j=0;j<HEIGHT;++j){
		for(int i=0;i<WIDTH;++i){
			image[i][j] = Vec3(0);
			for(int sample = 0; sample<TOTAL_SAMPLE; sample++){
				double ii = i + rand()/(double)RAND_MAX;
				double jj = j + rand()/(double)RAND_MAX;
				double xx = (2 * ((ii + 0.5) / WIDTH) - 1) * angle * aspectRatio;
				double yy = (1 - 2 * ((jj + 0.5) / HEIGHT)) * angle;
				Vec3 rayDirection(xx, yy, -1);
				rayDirection.normalize();
				image[i][j]+= sendRay(Vec3(0), rayDirection, 0, objects, lights);
			}
			image[i][j] = image[i][j] * (1/(double)TOTAL_SAMPLE);
		}
	}

	ofstream ofs("./image.ppm", ios::out);
	ofs << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";
	for(int j=0;j<HEIGHT;j++) {
		for(int i=0;i<WIDTH;i++){
			ofs<<int(min(1., image[i][j].x)*255)<<" ";
			ofs<<int(min(1., image[i][j].y)*255)<<" ";
			ofs<<int(min(1., image[i][j].z)*255)<<" ";
		}
		ofs<<endl;
	}
	ofs.close();
}
int main(){
	vector<Object*> objects;
	vector<Light> lights;
	Matrix m1(SCALE,Vec3(2,3,4));
	Matrix m2(SHEAR,Vec3(2,3,6),Vec3(2,1,3));
	m1 = m1 * m2;
	m1.print();
	m2 = m1.inverse();
	m2.print();
	(m1*m2).print();
	Sphere sp1(Vec3(0,-10004,-20), 10000, Vec3(0.2,0.2,0.2), 0, DIFFUSED);
	Sphere sp2(Vec3(0,0,-20), 4, Vec3(1,0.32,0.36), 0, SPECULAR);
	Cylinder cy1(Vec3(0,-5,-30), Vec3(0,1,0), 2, 10, Vec3(1,0.32,0.36), 0, SPECULAR);
	Cone co1(Vec3(0,-3,-20), Vec3(0,1,0),0.5, 3, Vec3(1,0.32,0.36), 0, SPECULAR);
	Triangle tr1(Vec3(0,-10,-50), Vec3(10,5,-50),Vec3(15, -10,-50), Vec3(1,0.32,0.36), 0.0, SPECULAR);
	Sphere sp3(Vec3(5,-1,-15), 2, Vec3(0.9,0.76,0.46), 0, SPECULAR);
	Sphere sp4(Vec3(5, 0, -25),3, Vec3(0.65,0.77,0.97), 0, SPECULAR);
	Sphere sp5(Vec3(-5,0,-15), 3, Vec3(0.9), 0, SPECULAR);
	objects.push_back(&sp1);
	objects.push_back(&tr1);
	// objects.push_back(&sp2);
	objects.push_back(&cy1);
	objects.push_back(&co1);
	objects.push_back(&sp3);
	objects.push_back(&sp4);
	objects.push_back(&sp5);
	lights.push_back(Light(Vec3(2,2,1), Vec3(30,30,3000)));
	// lights.push_back(Light(Vec3(-20,20,10), Vec3(0,1,3)));
	init(objects, lights);
}