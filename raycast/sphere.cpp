#include "sphere.h"


/**********************************************************************
 * This function intersects a ray with a given sphere 'sph'. You should
 * use the parametric representation of a line and do the intersection.
 * The function should return the parameter value for the intersection, 
 * which will be compared with others to determine which intersection
 * is closest. The value -1.0 is returned if there is no intersection
 *
 * If there is an intersection, the point of intersection should be
 * stored in the "hit" variable
 **********************************************************************/
float sphere::intersect_object(Point o, vec3 v, Point* hitPoint) {

	// delta = b^2 - 4ac
  float a = dot(v, v);
  float b = 2 * dot(v, (o - this->center));
  float c = dot(o - this->center, o - this->center) - pow(this->radius, 2);

  float delta = b*b - 4*a*c;
  
  // no intersection
  if(delta < 0) {
    return -1.0;
  } 

  float x1 = (-b + sqrt(delta)) / (2 * a);
  float x2 = (-b - sqrt(delta)) / (2 * a);

  float t = x1<x2 ? x1:x2;

  if (t < 0.0)
  {
    return -1.0;
  }

  *hitPoint = o + t * v;

  return t;
}

vec3 sphere::getNormal(Point point) {
  vec3 n = normalize(point - this->center);
  return n;
}

vec3 sphere::getCenter() {
  return this->center;
}

sphere::sphere() {
}
sphere::sphere(Point ctr, float rad, vec3 abm, vec3 dif,
     vec3 spe, float shine, float refl) 
:object(abm, dif, spe, shine, refl)
{
  this->center = ctr;
  this->radius = rad;  

  cout << "shpere " << index << endl;
}

sphere::~sphere() {
}



