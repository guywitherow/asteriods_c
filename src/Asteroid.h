#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "GlutHeaders.h"
#include "GenericTypes.h"
#include "Ship.h"

typedef struct {
	transform2d transform;
	vect2d movingDirection;
	collCircle hitCircle;
	boolean isLive;
} Asteroid;

Asteroid createAsteroid(Ship ship);

Asteroid moveAsteroid(Asteroid asteroid);

void drawAsteroid(Asteroid asteroid);


#endif