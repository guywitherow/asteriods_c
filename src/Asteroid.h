#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "GlutHeaders.h"
#include "GenericTypes.h"
#include "Ship.h"

#define SPAWNING_RAD 9.5
#define MAX_SPEED 5
#define MIN_SPEED 2
#define CIRCLE_POINTS 10

typedef struct {
	transform2d transform;
	vect2d movingDirection;
	collCircle hitCircle;
	boolean isLive;
} Asteroid;

Asteroid createAsteroid(Ship ship);

Asteroid moveAsteroid(Asteroid asteroid, float dt);

void drawAsteroid(Asteroid asteroid);
void removeAsteroid(Asteroid* array, int index, int array_length);

#endif