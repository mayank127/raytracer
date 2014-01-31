#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include "vec3.h"
#include "object.h"
using namespace std;

#define HEIGHT 480
#define WIDTH 640
#define RECURSION_DEPTH 5



Vec3 sendRay(Vec3 rayOrigin, Vec3 rayDirection, int level, vector<Object*> objects, vector<Vec3> lights){
	double intersectPoint = INFINITY;
	bool doesIntersect = false;
	Object* intersectObject = NULL;
	for(vector<Object*>::iterator it = objects.begin() ; it != objects.end(); ++it) {
		vector<double> points = (*it)->intersectionPoints(rayOrigin, rayDirection);
		if(points.size()==1){
			if(points[0]<0) continue;
			else{
				doesIntersect = true;
				if(intersectPoint > points[0]){
					intersectPoint = points[0];
					intersectObject = (*it);
				}
			}
		} else if(points.size()==2){

			if(points[0]>points[1]) {
				double temp = points[0];
				points[0] = points[1];
				points[1] = temp;
			}
			if(points[0]<0) points[0] = points[1];

			if(points[0]<0) continue;
			else{
				doesIntersect = true;
				if(intersectPoint > points[0]){
					intersectPoint = points[0];
					intersectObject = (*it);
				}
			}
		}
	}

	if(!doesIntersect) return Vec3(0);
	Vec3 point = rayOrigin + rayDirection * intersectPoint;
	Vec3 normal = intersectObject->getNormal(point);
	Vec3 finalColor(0);
	if(normal.dot(rayDirection)>0) normal = normal * -1;
	if(intersectObject->objectType == SPECULAR) {
		if(level < RECURSION_DEPTH) {
			Vec3 reflectionDir = rayDirection - normal * 2 * rayDirection.dot(normal);
			reflectionDir.normalize();
			Vec3 reflectionColor = sendRay(point + normal, reflectionDir, level + 1, objects, lights);
			finalColor += reflectionColor + intersectObject->surfaceColor;
		}
	} else{
		for(vector<Vec3>::iterator light = lights.begin() ; light != lights.end(); ++light) {
			Vec3 lightDir = (*light) - point;
			bool shadow = false;
			lightDir.normalize();
			for(vector<Object*>::iterator it = objects.begin() ; it != objects.end(); ++it){
				if((*it)->intersectionPoints(point, lightDir).size()>0){
					shadow = true;
					break;
				}
			}
			if(!shadow) finalColor += intersectObject->surfaceColor * normal.dot(lightDir);
		}
	}
	return finalColor;
}
double min(double x, double y){
	if(x>y) return y;
	return x;
}

void init(vector<Object*> objects, vector<Vec3> lights){
	double fov = 30, aspectRatio = WIDTH/(double) HEIGHT;
	double angle = tan((M_PI/2)*fov/180);

	vector<vector<Vec3> > image(WIDTH, vector<Vec3>(HEIGHT, Vec3()));
	for(int i=0;i<WIDTH;i++){
		for(int j=0;j<HEIGHT;j++){
			double xx = (2 * ((i + 0.5) / WIDTH) - 1) * angle * aspectRatio;
			double yy = (1 - 2 * ((j + 0.5) / HEIGHT)) * angle;
			Vec3 rayDirection(xx, yy, -1);
			rayDirection.normalize();
			image[i][j] = sendRay(Vec3(), rayDirection, 0, objects, lights);

			// cout<<image[i][j].x<<" "<<image[i][j].y<<" "<<image[i][j].z<<endl;
		}
	}

	ofstream ofs("./image.ppm", ios::out);
	ofs << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";
	for(int j=0;j<HEIGHT;j++) {
		for(int i=0;i<WIDTH;i++){
			ofs<<min(1, image[i][j].x)*255<<" ";
			ofs<<min(1, image[i][j].y)*255<<" ";
			ofs<<min(1, image[i][j].z)*255<<" ";
		}
		ofs<<endl;
	}
	ofs.close();
}
int main(){
	vector<Object*> objects;
	vector<Vec3> lights;
	Sphere sp1(Vec3(0,5,-55), 5, Vec3(1,0,0), 1, SPECULAR);
	Sphere sp2(Vec3(0,-5,-75), 5, Vec3(1,1,0), 1, SPECULAR);
	Sphere sp3(Vec3(-5,-20,-85), 5, Vec3(0,1,1), 1, DIFFUSED);
	Sphere sp4(Vec3(0, 0, -50), 5, Vec3(1,0,1), 1, SPECULAR);
	Sphere sp5(Vec3(-5,-15,-95), 10, Vec3(0,0,1), 1, SPECULAR);
	objects.push_back(&sp1);
	objects.push_back(&sp2);
	objects.push_back(&sp3);
	objects.push_back(&sp4);
	objects.push_back(&sp5);
	lights.push_back(Vec3(-1000,-1000,-1000));
	lights.push_back(Vec3(-1000,-500,-1000));

	init(objects, lights);
}