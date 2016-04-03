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

      if (hitPoint->x == -1)
      {
        cout << "now we got the far side" << endl;
      }
    }
    return t;
  }
}



bool sphere::getRefractedRayOutObject(Point p, vec3 l, Point& outPoint, vec3& refractedRayOut) {
  
  bool Refracted;
  vec3 rayIndisdeObj = refract(p, l, Refracted);
  if (!Refracted)
  {
    return false;
  }

  // find intersection
  Point hitPoint = vec3(-1, -1, -1);
  // get far side of intersection
  // in case this is a sphere
  float dst = intersect_object(p, rayIndisdeObj, &hitPoint, false);
  if (dst < precision)
  {
    return false;
  }

  refractedRayOut = refract(hitPoint, -rayIndisdeObj, Refracted);
  if (!Refracted)
  {
    return false;
  }

  outPoint = hitPoint;

  return true;
}


// do one single refraction
// return fefracted array
vec3 sphere::refract(Point p, vec3 l, bool& isRefracted) {
  vec3 refractedRay;
  vec3 n = getNormal(p);

  float r_index;
  if (dot(n, l) > 0) {
    r_index = 1.0 / this->refractive_index;
  } else {
    // going out of the object
    r_index = this->transmissivity;
    n = -n;
  }

  float delta = 1 - pow(r_index, 2) * (1.0 - pow(dot(n, l), 2));

  if (delta < 0.0)
  {
    isRefracted = false;
  } else {
    isRefracted = true;
    refractedRay = n * (r_index * dot(n, l) - sqrt(delta)) - r_index * l;
  }

  //cout << "probably: " << isRefracted << endl;
  return normalize(refractedRay);
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
