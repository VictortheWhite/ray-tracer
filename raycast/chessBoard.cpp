#include "chessBoard.h"

	chessBoard::chessBoard() {
		this->normal = vec3(0, 1, 0);
		this->pOrigin = vec3(0.0, -2.5, -3.5);
		this->width = 200;
	}
	chessBoard::~chessBoard() {}

	vec3 chessBoard::getAmbient(Point) {
		return vec3(1,1,1);
	}

  	vec3 chessBoard::getDiffuse(Point) {
  		return vec3(1,1,1);
  	}

  	vec3 chessBoard::getSpecular(Point) {
  		return vec3(1.0, 1.0, 1.0);
  	}
  	float chessBoard::getShineness(Point) {
  		return 25;
  	}
  	float chessBoard::getReflectance(Point) {
  		return 0.6;
  	}


	vec3 chessBoard::getNormal(Point Point) {
		return this->normal;
	}

  	bool chessBoard::in_shadow(Point p, Point LightSource, vector<object*> &objects) {
  		return false;
  	}

  	float chessBoard::intersect_object(Point o, vec3 v, Point* hitPoint) {
  		// parallel
  		if (dot(v, normal) == 0)
  		{
  			return -1.0;
  		}

  		float t = (dot(pOrigin, normal) - dot(o, normal)) / dot(v, normal);

  		*hitPoint = o + t * v;

  		return t;
  	}