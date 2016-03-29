#include "sphere.h"


/*********************************************************************
 * This function returns a pointer to the sphere object that the
 * ray intersects first; NULL if no intersection. You should decide
 * which arguments to use for the function. For exmaple, note that you
 * should return the point of intersection to the calling function.
 **********************************************************************/
sphere* sphere::intersect_scene(Point origin, vec3 v, sphere** spheres) {
  int numOfSpheres = 3;

  sphere *sph = NULL;
  float dst = std::numeric_limits<float>::infinity();

  for (int i = 0; i < numOfSpheres; ++i)
  {
    float temDst = spheres[i]->intersect_sphere(origin, v);
    if (temDst < dst)
    {
      sph = spheres[i];
      dst = temDst;
    }
  }

  if (dst == -1.0)
  {
    return NULL;
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
float sphere::intersect_sphere(Point o, vec3 v) {
	// delta = b^2 - 4ac

  //cout << "give me some thit " << endl;
  float b = 2 * dot(v, (o-this->center));
  float a = dot(v, v);
  float c = dot(o - this->center, o - this->center) - pow(this->radius, 2);

  float delta = pow(b, 2) - 4*a*c;
  
  //cout << "delta" << delta << endl;

  // no intersection
  if(delta < 0) {
    cout << delta << endl; 
    return -1.0;
  } else {
  }

  float x1 = (-b + sqrt(delta)) / (2 * a);
  float x2 = (-b - sqrt(delta)) / (2 * a);

  float t = x1>x2 ? x1:x2;

  this->hitPoint = o + t * v;

  //cout << t << ' ' << hitPoint  << endl;

  return t;
}



Point sphere::getHitPoint() {
  return this->hitPoint;
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



