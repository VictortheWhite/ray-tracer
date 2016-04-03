#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "object.h"

class chessBoard : public object
{

private:
	vec3 normal;
	Point pOrigin;	// center of the chess board
	float width;

public:
	chessBoard();
	~chessBoard();

	vec3 getAmbient(Point);
  	vec3 getDiffuse(Point);
  	vec3 getSpecular(Point);
  	float getShineness(Point);
  	float getReflectance(Point);


	vec3 getNormal(Point Point);
  	float intersect_object(Point, vec3, Point*);	
};



#endif