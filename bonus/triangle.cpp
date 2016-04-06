#include "triangle.h"

extern vector<object*> scene;

float triangle::intersect_object(Point o, vec3 v, Point* hitPoint) {

	return intersect_object(o, v, hitPoint, false);
	/*
	if (dot(v, normal) >= 0)
	{
	   // parallel
 	   return -1.0;
	}

 	float t = dot(vertexA-o, normal) / dot(v, normal);

 	if (t < precision)
	{
	  // no intersection
  	  return -1.0;
 	}

  	*hitPoint = o + t * v;

	if (this->IsPointInTriangle(*hitPoint)) 
		return t;
	else 
		return -1.0;
	*/
}

float triangle::intersect_object(Point o, vec3 v, Point* hitPoint, bool fromBack) {
	if (!fromBack && dot(v, normal) >= 0)
	{
	   // parallel
 	   return -1.0;
	}

	if (fromBack && dot(v, normal) <= 0)
	{
		return -1.0;
	}

 	float t = dot(vertexA-o, normal) / dot(v, normal);

 	if (t < precision)
	{
	  // no intersection
  	  return -1.0;
 	}

  	*hitPoint = o + t * v;

	if (this->IsPointInTriangle(*hitPoint)) 
		return t;
	else 
		return -1.0;
}

bool triangle::IsPointInTriangle(Point p) {
	
	vec3 PA = vertexA - p;
	vec3 PB = vertexB - p;
	vec3 PC = vertexC - p;

	vec3 n1 = cross(PA, PB);
	vec3 n2 = cross(PB, PC);
	vec3 n3 = cross(PC, PA);

	return (dot(n1, n2) >= 0) && (dot(n1, n3) >= 0); 
}


object* triangle::intersectTriangleInMesh(Point origin, vec3 v, vector<object*>& objects, Point *hitPoint, object* ignore) {
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
    float tempDst = objects[i]->intersect_object(origin, v, &tempHit, false);

    if (tempDst >= precision && tempDst < dst)
    {
      obj = objects[i];
      dst = tempDst;
      *hitPoint = tempHit;
    }
  }

  return obj;
}


bool triangle::getRefractedRayOutObject(Point p, vec3 l, Point& outPoint, vec3& refractedRayOut) {
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
  	object* obj= intersectTriangleInMesh(p, rayIndisdeObj, scene, &hitPoint, this);
  	if (obj == NULL)
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

vec3 triangle::refract(Point p, vec3 l, bool& isRefracted) {

	vec3 refractedRay;
  	vec3 n = getNormal(p);

  	float r_index;
  	if (dot(n, l) > 0) {
    	r_index = 1.0 / this->refractive_index;
  	} else {
    	// going out of the object
    	r_index = this->refractive_index;
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


vec3 triangle::getNormal(Point Point) {
	return this->normal;
}


// constructors and destructor
triangle::triangle() { }
triangle::triangle( vec3 vertices[], vec3 abm, vec3 dif,
     vec3 spe, float shine, float refl, float refra, 
     float trans, float dif_co )
: object(abm, dif, spe, shine, refl, refra, trans, dif_co) {
	
	this->vertexA = vertices[0];
	this->vertexB = vertices[1];
	this->vertexC = vertices[2];

	// compute normal
	this->normal = normalize(cross(vertexB-vertexA, vertexC-vertexA));
} 
triangle::~triangle() { }