#include "triangle.h"


float triangle::intersect_object(Point o, vec3 v, Point* hitPoint) {
	if (dot(v, normal) == 0)
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

	if (this->IsPointInTriangle(*hitPoint)) {
		cout << "shit" << endl;
		return t;
	}
	else {
		//cout << "fuck" << endl;
		return -1.0;
	}
}

bool triangle::IsPointInTriangle(Point p) {
	
	vec3 PA = vertexA - p;
	vec3 PB = vertexB - p;
	vec3 PC = vertexC - p;

	vec3 n1 = cross(PA, PB);
	vec3 n2 = cross(PB, PC);
	vec3 n3 = cross(PC, PA);

	//cout << dot(n1, n2) << "  " << dot(n1, n3) << " "<< dot(n2, n3)<<endl;

	//cout << dot(n1, normal) << " " << dot(n2, normal) << " " << dot(n3, normal) << endl;

	return (dot(n1, n2) >= 0) && (dot(n1, n3) >= 0); 
	
	/*
	vec3 AP = p - vertexA;
	vec3 AB = vertexB - vertexA;
	if (dot(normal, cross(AP, AB)) <= 0)
	{
		return false;
	}

	vec3 BP = p - vertexB;
	vec3 BC = vertexC - vertexB;
	if (dot(normal, cross(BP, BC)) <= 0)
	{
		return false;
	}

	vec3 CP = p - vertexC;
	vec3 CA = vertexA - vertexC;
	if (dot(normal, cross(CP, CA)) <= 0)
	{
		return false;
	}
	*/ 
	//return true;
}

bool triangle::getRefractedRayOutObject(Point p, vec3 l, Point& outPoint, vec3& refractedRayOut) {
	return false;
}

vec3 triangle::refract(Point p, vec3 l, bool& isRefracted) {

	isRefracted = false;
	return vec3();
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
	
	vec3 shift = vec3(0, -0.75, -1);

	this->vertexA = vertices[0] +shift;
	this->vertexB = vertices[1] +shift;
	this->vertexC = vertices[2] +shift;

	// compute normal
	this->normal = normalize(cross(vertexB-vertexA, vertexC-vertexA));
} 
triangle::~triangle() { }