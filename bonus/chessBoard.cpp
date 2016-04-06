#include "chessBoard.h"

chessBoard::chessBoard() : object(1.55, 0, 0.1)
{
	this->normal = vec3(0, 1, 0);
	this->pOrigin = vec3(0.0, -2.5, -3.5);
	this->width = 8;
}
chessBoard::~chessBoard() {}

vec3 chessBoard::getAmbient(Point p) {
	int x = (int)(p-pOrigin-width).x;
	int y = (int)(p-pOrigin-width).z;

	if ( (x+y)%2 == 0) {
		return vec3(0.5, 0.5, 0.5);
	} else {
		return vec3(0.1,0.1,0.1);
	}
}

vec3 chessBoard::getDiffuse(Point p) {

	int x = (int)(p-pOrigin-width).x;
	int y = (int)(p-pOrigin-width).z;

	if ( (x+y)%2 == 0) {
		return vec3(1.0, 1.0, 1.0);
	} else {
		return vec3(0.2,0.2,0.2);
	}
}

vec3 chessBoard::getSpecular(Point p) {
   return vec3(0, 0, 0);
}

float chessBoard::getShineness(Point p) {
	return 35;
}

float chessBoard::getReflectance(Point p) {
	return 0.3;
}


vec3 chessBoard::getNormal(Point p) {
	return this->normal;
}

float chessBoard::intersect_object(Point o, vec3 v, Point* hitPoint) {

	// parallel
	if (dot(v, normal) == 0)
	{
 	   return -1.0;
	}

 	float t = dot(pOrigin-o, normal) / dot(v, normal);

 	if (t < precision)
	{
  	  return -1.0;
 	}

  	*hitPoint = o + t * v;

  	if (fabs((*hitPoint-pOrigin).x) > width)
  	{
  		return -1.0;
  	}

  	if (fabs((*hitPoint-pOrigin).z) > width)
  	{
  		return -1.0;
  	}

	return t;
}


bool chessBoard::getRefractedRayOutObject(Point p, vec3 l, Point& outPoint, vec3& refractedRayOut) {
	return false;
}

vec3 chessBoard::refract(Point p, vec3 l, bool& isRefracted) {
	return vec3();
}
