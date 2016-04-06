#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "object.h"

class chessBoard : public object
{

private:
	vec3 normal;
	Point pOrigin;	// center of the chess board
	float width;

	vec3 refract(Point p, vec3 l, bool& isRefracted);
	float intersect_object(Point, vec3, Point*);	


public:
	chessBoard(int width);
	~chessBoard();

	vec3 getAmbient(Point);
  	vec3 getDiffuse(Point);
  	vec3 getSpecular(Point);
  	float getShineness(Point);
  	float getReflectance(Point);

	vec3 getNormal(Point Point);
  	bool getRefractedRayOutObject(Point p, vec3 l, Point& outPoint, vec3& refractedRayOut);
};



#endif