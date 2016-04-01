#ifndef OBJECT_H
#define OBJECT_H

#include "include/Angel.h"
#include <limits>


using namespace std;

typedef Angel::vec3 Point;
typedef Angel::vec3 Color;

class object
{

protected:
	int index;

	vec3 ambient;
  	vec3 diffuse;
  	vec3 specular;
  	float shineness;
  	float reflectance;

public:
	object();
	object(vec3, vec3, vec3, float, float);
	virtual ~object();

  vec3 getAmbient(Point);
  vec3 getDiffuse(Point);
  vec3 getSpecular(Point);
  float getShineness(Point);
  float getReflectance(Point);


	virtual vec3 getNormal(Point Point) = 0;
  virtual bool in_shadow(Point, Point, object**) = 0;
  virtual float intersect_object(Point, vec3, Point*) = 0;

  static object* intersect_scene(Point o, vec3 v, object** objects, Point* hitPoint, object* ignore);


};








#endif