#ifndef TRACER_H
#define TRACER_H

#include "sphere.h"
//#include <GL/glut.h>
#include <math.h>
#include "global.h"
#include "sphere.h"
using namespace std;

class tracer
{

private:
	vec3 **frame;
	sphere **scene;

	int win_width;
	int win_height;

	float image_width;
	float image_height;
	float image_plane;

	Point eye_pos;
	Color background_clr;
	Color null_clr;

	Point LightSource;
	vec3  LightIntensity;
	vec3  global_ambient;

	float decay_a;
	float decay_b;
	float decay_c;

	bool shadow_on;
	bool reflection_on;
	bool stochastic_on;

	Color recursive_ray_trace(vec3 ray, int step_max);
	Color phong(Point p, vec3 v, sphere *sph);

	// helper methods
	float max(float, float);

public:
	tracer(
		vec3 **frame,
		int wWidth,
		int wHeight,
		float iWidth,
		float iHeight,
		float image,
		Point Eye,
		Color bgclr,
		Color nullclr,
		Point LightSource,
		vec3 LightIntensity,
		vec3 global_ambient, 
		float decayA,
		float decayB,
		float decayC,
		sphere **scene
		);
	~tracer();
	

	void ray_trace(
		// some options 
		int step_max
		);

	void set(bool, bool, bool);

};


#endif