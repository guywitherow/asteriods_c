#ifndef SHIP_H
#define SHIP_H

#include "GlutHeaders.h"
#include "GenericTypes.h"
#define rotationSpeed 200.0

typedef struct {
	transform2d transform;
	vect2d speed;
	boolean firing;
	collCircle warningCollision;
	collCircle hitCircle;
} Ship;

void drawShip(Ship ship);

Ship moveShip(Ship ship, float dt, float speedAmount);

Ship rotShip(Ship ship, float rotDirection, float dt);

float circlePos(float degree, float r, boolean isX);

#endif