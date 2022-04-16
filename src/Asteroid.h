#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "GlutHeaders.h"
#include "GenericTypes.h"
#include "Ship.h"

#define SPAWNING_RAD 9.5
#define MAX_SPEED .3
#define MIN_SPEED .2
#define MAX_SIZE .55
#define MIN_SIZE .25
#define MAX_SPIN 1.0
#define MIN_SPIN -1.0

#define VARIANCE .1

#define CIRCLE_POINTS 10


typedef struct {
	transform2d transform;
	vect2d movingDirection;
	collCircle hitCircle;
	boolean isLive;
	int pointCount;
	float spikeSeed;
	float rotSpeed;
	int HP;
	boolean insideArena;
	int isTouching;
} Asteroid;

Asteroid createAsteroid(Ship ship);

Asteroid moveAsteroid(Asteroid asteroid, float dt);

void drawAsteroid(Asteroid asteroid);
void removeAsteroid(Asteroid* array, int index, int array_length);

#endif