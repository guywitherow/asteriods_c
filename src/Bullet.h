#ifndef BULLET_H
#define BULLET_H

#include "GlutHeaders.h"
#include "GenericTypes.h"

typedef struct {
	transform2d transform;
	vect2d movingDirection;
	collCircle hitCircle;
	boolean isLive;
} Bullet;

void drawBullet(Bullet bullet);

Bullet moveBullet(Bullet bullet, float dt);

#endif