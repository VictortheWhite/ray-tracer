#include "object.h"


object::object() {}
object::object(vec3 abm, vec3 dif, vec3 spe, float shine, float refl) {
  static int INDEX = 0;
  this->ambient = abm;
  this->diffuse = dif;
  this->specular = spe;
  this->shineness = shine;
  this->reflectance = refl;

  this->index = INDEX++;
}
object::~object() {}


vec3 object::getAmbient(Point p) {
  return this->ambient;
}
vec3 object::getDiffuse(Point p) {
  return this->diffuse;
}
vec3 object::getSpecular(Point p) {
  return this->specular;
}
float object::getShineness(Point p) {
  return this->shineness;
}
float object::getReflectance(Point p) {
 return this->reflectance;
}


//vec3 getNormal(Point) = 0;
//bool in_shadow() = 0;

//float intersect_object(Point, vec3, Point*) = 0;

/*********************************************************************
 * This function returns a pointer to the sphere object that the
 * ray intersects first; NULL if no intersection. You should decide
 * which arguments to use for the function. For exmaple, note that you
 * should return the point of intersection to the calling function.
 **********************************************************************/
object* object::intersect_scene(Point origin, vec3 v, object** objects, Point* hitPoint, object* ignore) {
  int numOfObjects = 3;

  object *obj = NULL;
  float dst = std::numeric_limits<float>::infinity();

  for (int i = 0; i < numOfObjects; ++i)
  {
    if (objects[i] == ignore)
    {
      // if intersects with ignored shpere
      // ignore
      continue;
    }

    float tempDst = objects[i]->intersect_object(origin, v, hitPoint);
    if (tempDst >= 0.0 && tempDst < dst)
    {
      obj = objects[i];
      dst = tempDst;
    }
  }

  return obj;
}