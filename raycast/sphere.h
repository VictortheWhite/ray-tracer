#ifndef SPHERE_H
#define SPHERE_H

#include "include/Angel.h"
#include "math.h"

using namespace std;

typedef Angel::vec3 Point;
typedef Angel::vec3 Color;

class sphere
{
private:
  int index;

  Point center;
  float radius;

  float mat_ambient[3];
  float mat_diffuse[3];
  float mat_specular[3];
  float mat_shineness;

  GLfloat reflectance;


private:
  float intersect_sphere(Point origin, vec3 v, sphere sph, Point* hitPoint);

public:
  sphere();
  sphere(vec3 ctr, float rad, float abm[], float dif[],
     float spe[], float shine, float refl);
  ~sphere();

  vec3 getNormal(Point Point);
  sphere* intersect_scene(Point origin, vec3 v, sphere** spheres, Point* hitPoint);
  
};



#endif