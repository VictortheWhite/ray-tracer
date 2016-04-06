#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object.h"

class triangle : public object
{

private:
	Point vertexA;
	Point vertexB;
	Point vertexC;
	vec3  normal;

	float intersect_object(Point o, vec3 v, Point* hitPoint);
	vec3 refract(Point p, vec3 l, bool& isRefracted);

	bool IsPointInTriangle(Point p);

public:
	triangle();
	triangle(vec3 vertices[], vec3 abm, vec3 dif,
     vec3 spe, float shine, float refl, float refra, 
     float trans, float dif_co);
	~triangle();
	
	vec3 getNormal(Point point);
	bool getRefractedRayOutObject(Point p, vec3 l, Point& outPoint, vec3& refractedRayOut);
};







#endif