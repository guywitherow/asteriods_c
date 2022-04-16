#ifndef TYPES_H
#define TYPES_H

#include "GlutHeaders.h"

#define PI 3.14159265

typedef struct {
	float x;
	float y;
} point2d;


typedef struct {
	float x;
	float y;
} vect2d;

typedef struct {
	point2d pos;
	float radius;
} collCircle;

typedef struct {
	point2d position;
	float rotation;
	vect2d scale;
} transform2d;


float circlePos(float degree, float r, boolean isX);

#endif