#ifndef TRACER_H
#define TRACER_H

#include "sphere.h"
//#include <GL/glut.h>
#include <math.h>
#include <ctime>
#include "global.h"
#include "sphere.h"
#include "object.h"
using namespace std;

class tracer
{

private:
	vec3 **frame;
	vector<object*> scene;

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

	int step_max;

	bool shadow_on;
	bool reflection_on;
	bool refraction_on;
	bool stochastic_on;
	bool supersampling_on;


	Color recursive_ray_trace(Point o, vec3 ray, int step, object* ignore);
	Color phong(Point p, vec3 v, object *obj, int step);
	vec3  generateDiffuseRay(vec3 n);

	// helper methods
	float max(float, float);
	float randFloat(float, float);

	static const int numOfStochasticRay = 5;

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
		Point lightSource,
		vec3 lightIntensity,
		vec3 global_ambient, 
		float decayA,
		float decayB,
		float decayC,
		vector<object*> scene
		);
	~tracer();
	

	void ray_trace(
		// some options 
		int step_max
		);

	void set(bool, bool, bool, bool, bool);

};


#endif