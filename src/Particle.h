#ifndef PARTICLE_H
#define PARTICLE_H

#include "GlutHeaders.h"
#include "GenericTypes.h"

#define MAX_PARTICLE_SPEED 20
#define MIN_PARTICLE_SPEED 3

typedef struct {
	point2d position;
	vect2d movingDirection;
	float transparency;
	boolean isLive;
} Particle;

void drawParticle(Particle particle);

Particle createParticle(float x, float y);

Particle moveParticle(Particle particle, float dt);

#endif