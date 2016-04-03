#ifndef SPHERE_H
#define SPHERE_H

//#include "include/Angel.h"
#include "object.h"
#include <vector>
//#include "math.h"

using namespace std;

//typedef Angel::vec3 Point;
//typedef Angel::vec3 Color;

class sphere : public object
{
private:
  Point center;
  float radius;

  float intersect_object(Point o, vec3 v, Point* hitPoint);
  float intersect_object(Point o, vec3 v, Point* hitPoint, bool getNearSide);

public:
  sphere();
  sphere(vec3 ctr, float rad, vec3 abm, vec3 dif,
     vec3 spe, float shine, float refl, float refra, float trans);
  ~sphere();

  vec3 getCenter();
  vec3 getNormal(Point point);

  //bool in_shadow(Point p, Point lightSource, vector<object*> &objects);
};



#endif