#ifndef BULLET_H
#define BULLET_H

#include "GlutHeaders.h"
#include "GenericTypes.h"
#include "Ship.h"
#include "Asteroid.h"

#define BULLET_SPEED 5

typedef struct {
	transform2d transform;
	vect2d movingDirection;
	collCircle hitCircle;
	boolean isLive;
	boolean chaser;
} Bullet;

void drawBullet(Bullet bullet);

Bullet createBullet(Ship ship);

Bullet moveBullet(Bullet bullet, float dt, point2d chasePoint, int closestIndex);

void removeBullet(Bullet* array, int index, int array_length);

#endif