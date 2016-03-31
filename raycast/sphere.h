#ifndef SPHERE_H
#define SPHERE_H

#include "include/Angel.h"
#include "math.h"
#include <limits>

using namespace std;

typedef Angel::vec3 Point;
typedef Angel::vec3 Color;

class sphere
{
private:
  int index;

  Point center;
  float radius;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shineness;

  float reflectance;

private:
  float intersect_sphere(Point origin, vec3 v, Point* hitPoint);

public:
  sphere();
  sphere(vec3 ctr, float rad, vec3 abm, vec3 dif,
     vec3 spe, float shine, float refl);
  ~sphere();

  sphere* intersect_scene(Point o, vec3 v, sphere** spheres, Point* hitPoint);

  bool in_shadow(Point p, Point lightSource, sphere** spheres);

  vec3 getNormal(Point Point);
  vec3 getAmbient();
  vec3 getDiffuse();
  vec3 getSpecular();
  float getShineness();
  float getReflectance();

  vec3 getCenter();
  
};



#endif