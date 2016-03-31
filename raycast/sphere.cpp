#include "sphere.h"


/*********************************************************************
 * This function returns a pointer to the sphere object that the
 * ray intersects first; NULL if no intersection. You should decide
 * which arguments to use for the function. For exmaple, note that you
 * should return the point of intersection to the calling function.
 **********************************************************************/
sphere* sphere::intersect_scene(Point origin, vec3 v, sphere** spheres, Point* hitPoint, sphere* ignore) {
  int numOfSpheres = 3;

  sphere *sph = NULL;
  float dst = std::numeric_limits<float>::infinity();

  for (int i = 0; i < numOfSpheres; ++i)
  {
    if (spheres[i] == ignore)
    {
      // if intersects with ignored shpere
      // ignore
      continue;
    }

    float tempDst = spheres[i]->intersect_sphere(origin, v, hitPoint);
    if (tempDst >= 0.0 && tempDst < dst)
    {
      sph = spheres[i];
      dst = tempDst;
    }
  }

  return sph;
}


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
float sphere::intersect_sphere(Point o, vec3 v, Point* hitPoint) {
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

  *hitPoint = o + t * v;

  return t;
}

vec3 sphere::getNormal(Point point) {
  return normalize(point - this->center);
}


vec3 sphere::getAmbient() {
  return this->ambient;
}
vec3 sphere::getDiffuse() {
  return this->diffuse;
}
vec3 sphere::getSpecular() {
  return this->specular;
}
float sphere::getShineness() {
  return this->shineness;
}
float sphere::getReflectance() {
 return this->reflectance;
}

vec3 sphere::getCenter() {
  return this->center;
}


bool sphere::in_shadow(Point p, Point lightSource, sphere** spheres) {

  Point hitPoint;

  sphere *sph = intersect_scene(p, normalize(lightSource-p), spheres, &hitPoint, this);

  return sph != NULL;
}


sphere::sphere() {}
sphere::sphere(Point ctr, float rad, vec3 abm, vec3 dif,
     vec3 spe, float shine, float refl) {
  static int INDEX = 0;
  this->center = ctr;
  this->radius = rad;

  this->ambient = abm;
  this->diffuse = dif;
  this->specular = spe;
  this->shineness = shine;
  this->reflectance = refl;

  this->index = INDEX++;
}

sphere::~sphere() {}



