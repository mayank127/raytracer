#include <iostream>
#include <cmath>
#include "vec3.h"
using namespace std;

#define HEIGHT 480
#define WIDTH 640


int main(){
	double fov = 30, aspectRatio = WIDTH/(double) HEIGHT;
	double angle = tan((M_PI/2)*fov/180);

	vector<vector<Vec3> > image(WIDTH, vector<Vec3>(HEIGHT, Vec3()));
	for(int i=0;i<WIDTH;i++){
		for(int j=0;j<HEIGHT;j++){
			double xx = (2 * ((x + 0.5) / WIDTH) - 1) * angle * aspectratio;
			double yy = (1 - 2 * ((y + 0.5) / HEIGHT)) * angle;
			Vec3 rayDirection(xx, yy, -1);
			rayDirection.normalize();
			image[i][j] = sendRay(Vec3(), rayDirection);
		}
	}
}