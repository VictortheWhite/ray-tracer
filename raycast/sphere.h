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

  float mat_ambient[3];
  float mat_diffuse[3];
  float mat_specular[3];
  float mat_shineness;

  GLfloat reflectance;

  Point hitPoint;


private:
  float intersect_sphere(Point origin, vec3 v);

public:
  sphere();
  sphere(vec3 ctr, float rad, float abm[], float dif[],
     float spe[], float shine, float refl);
  ~sphere();

  vec3 getNormal(Point Point);
  Point getHitPoint();
  sphere* intersect_scene(Point o, vec3 v, sphere** spheres);
  
};



#endif