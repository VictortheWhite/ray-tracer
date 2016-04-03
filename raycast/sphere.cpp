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

  /*
	// delta = b^2 - 4ac
  float a = dot(v, v);
  float b = 2 * dot(v, (o - this->center));
  float c = dot(o - this->center, o - this->center) - pow(this->radius, 2);

  float delta = b*b - 4*a*c;
  
  if (hitPoint->x == -1.0)
  {
    //cout << a << " " << b << " " << c << " " << delta << endl;
  }

  // no intersection
  if(delta < precision) {
    return -1.0;
  } 

  float x1 = (-b + sqrt(delta)) / (2 * a);
  float x2 = (-b - sqrt(delta)) / (2 * a);

  float t = x1<x2 ? x1:x2;

  if (t < 0.0)
  {
    if (hitPoint->x == -1.0) cout << t << endl;
    return -1.0;
  }

  *hitPoint = o + t * v;

  return t;
  */
  // get near side by default
  return this->intersect_object(o, v, hitPoint, true);
}

// this function is defined here
// in case I want the far side of intersectint point of a sphere
float sphere::intersect_object(Point o, vec3 v, Point* hitPoint, bool getNearSide) {
  // delta = b^2 - 4ac
  float a = dot(v, v);
  float b = 2 * dot(v, (o - this->center));
  float c = dot(o - this->center, o - this->center) - pow(this->radius, 2);

  float delta = b*b - 4*a*c;
  
  if (hitPoint->x == -1.0)
  {
    //cout << a << " " << b << " " << c << " " << delta << endl;
  }

  // no intersection
  if(delta < precision) {
    return -1.0;
  } 

  float x1 = (-b + sqrt(delta)) / (2 * a);
  float x2 = (-b - sqrt(delta)) / (2 * a);

  if (x1 < 0)
  {
    // no intersection
    return -1.0;
  } else if( x2 < 0 ){
    // one intersection, which is the far side
    float t = x1;
    *hitPoint = o + t * v;
    return t;
  } else {
    // two intersections
    float t;
    if (getNearSide)
    {
      t = x2;
      *hitPoint = o + t * v;
    } else {
      // get far side
      t = x1;
      *hitPoint = o + t * v;
    }
    return t;
  }
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
     vec3 spe, float shine, float refl, float refra, float trans) 
:object(abm, dif, spe, shine, refl, refra, trans)
{
  this->center = ctr;
  this->radius = rad;  
}

sphere::~sphere() {
}



