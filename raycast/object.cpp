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


bool object::getRefractedRayOutObject(Point p, vec3 l, Point& outPoint, vec3& refractedRayOut) {
  vec3 rayIndisdeObj;

  static int a = 0;
  static int b = 0;
  static int c = 0;


  bool Refracted;
  rayIndisdeObj = refract(p, l, Refracted);
  if (!Refracted)
  {
    return false;
  }

  // find intersection
  Point hitPoint = vec3(-1, -1, -1);
  // get far side of intersection
  // in case this is a sphere
  float dst = this->intersect_object(p, rayIndisdeObj, &hitPoint, false);
  if (dst < precision)
  {
    if (this->index != 3)
    {
      //cout << "c" <<c++ << endl;
      //cout << dst << endl;
    }
    return false;
  }

  refractedRayOut = refract(hitPoint, -rayIndisdeObj, Refracted);
  if (!Refracted)
  {
    if (this->index != 3)
    {
      cout << "a" <<a++ << endl;;
    }
    return false;
  }

  outPoint = hitPoint;

    if (this->index != 3)
    {
      //cout << "b" <<b++ << endl;;
    }
  return true;
}


// do one single refraction
// return fefracted array
vec3 object::refract(Point p, vec3 l, bool& isRefracted) {
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
