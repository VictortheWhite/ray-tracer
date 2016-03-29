#include "sphere.h"


/*********************************************************************
 * This function returns a pointer to the sphere object that the
 * ray intersects first; NULL if no intersection. You should decide
 * which arguments to use for the function. For exmaple, note that you
 * should return the point of intersection to the calling function.
 **********************************************************************/
sphere* sphere::intersect_scene(Point origin, vec3 v, sphere** spheres, Point* hitPoint) {
  return NULL;
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
float sphere::intersect_sphere(Point origin, vec3 v, sphere sph, Point* hitPoint) {
	return 0.0;
}

vec3 sphere::getNormal(Point point) {
  return normalize(point - this->center);
}

sphere::sphere() {}
sphere::sphere(Point ctr, float rad, float abm[], float dif[],
     float spe[], float shine, float refl) {
  static int INDEX = 0;
  this->center = ctr;
  this->radius = rad;
  for (int i = 0; i < 3; ++i)
  {
    this->mat_ambient[i] = abm[i];
  }
  for (int i = 0; i < 3; ++i)
  {
    this->mat_diffuse[i] = dif[i];
  }
  for (int i = 0; i < 3; ++i)
  {
    this->mat_specular[i] = spe[i];
  }
  this->mat_shineness = shine;
  this->reflectance = refl;

  this->index = INDEX++;
}

sphere::~sphere() {}



