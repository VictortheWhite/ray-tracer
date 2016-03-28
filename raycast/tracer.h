#ifndef TRACER_H
#define TRACER_H

#include "sphere.h"
//#include <GL/glut.h>
#include <math.h>
#include "global.h"

class tracer
{

private:
	vec3 **frame;

	int win_width;
	int win_height;

	float image_width;
	float image_height;
	float image_plane;

	Point eye_pos;
	Color background_clr;
	Color null_clr;

	sphere **scene;

	Point *LightSource;
	float *LightItensity;
	float *global_ambient;

	float decay_a;
	float decay_b;
	float decay_c;

	Color recursive_ray_trace();

	Color phong(Point p, vec3 v, vec3 surf_norm, sphere *sph);


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
		Color nullclr
		);
	~tracer();
	

	void ray_trace(
		// some options 
		bool shadow_on,
		int step_max
		);

};


#endif