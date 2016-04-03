#include "object.h"

static int INDEX = 0;

object::object() {}
object::object(float refra, float trans) { 
  this->refractive_index = refra;
  this->transmissivity = trans; 

  this->index = INDEX++;
}
object::object(vec3 abm, vec3 dif, vec3 spe, 
  float shine, float refl, float refra, float trans) 
{
  this->ambient = abm;
  this->diffuse = dif;
  this->specular = spe;
  this->shineness = shine;
  this->reflectance = refl;
  this->refractive_index = refra;
  this->transmissivity = trans;

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
float object::getTransmissivity() {
  return this->transmissivity;
}
float object::getRefractiveIndex() {
  return this->refractive_index;
}


int object::getIndex() {
  return this->index;
}

/*********************************************************************
 * This function returns a pointer to the sphere object that the
 * ray intersects first; NULL if no intersection. You should decide
 * which arguments to use for the function. For exmaple, note that you
 * should return the point of intersection to the calling function.
 **********************************************************************/
object* object::intersect_scene(Point origin, vec3 v, vector<object*> &objects, Point* hitPoint, object* ignore) {
  int numOfObjects = objects.size();

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

    vec3 tempHit;
    float tempDst = objects[i]->intersect_object(origin, v, &tempHit);

    if (tempDst >= precision && tempDst < dst)
    {
      obj = objects[i];
      dst = tempDst;
      *hitPoint = tempHit;
    }
  }

  return obj;
}

float object::intersect_object(Point o, vec3 v, Point* hitPoint, bool getNearSide) {
  return intersect_object(o, v, hitPoint);
}

bool object::in_shadow(Point p, Point lightSource, vector<object*> &objects) {

  Point hitPoint;

  object *obj = intersect_scene(p, normalize(lightSource-p), objects, &hitPoint, this);

  return obj != NULL;
}


