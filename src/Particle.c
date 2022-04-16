
#include "Particle.h"

void drawParticle(Particle particle) {
	//draw dot
	glColor4f(0.3, 0.3, 0.3, particle.transparency);
	glPointSize(2.0f);
	glBegin(GL_POINTS);
	glVertex2f(particle.position.x, particle.position.y);
	glEnd();
}

Particle moveParticle(Particle particle, float dt) {
	float newParPosX = particle.position.x + (particle.movingDirection.x * dt);
	float newParPosY = particle.position.y + (particle.movingDirection.y * dt);
	point2d newParPos = { newParPosX ,newParPosY };
	particle.position = newParPos;
	return particle;
}

Particle createParticle(float x, float y) {
	point2d newPoint = {x,y};

	float directionX = fmod(rand(), MAX_PARTICLE_SPEED + MIN_PARTICLE_SPEED) - MIN_PARTICLE_SPEED;
	float directionY = fmod(rand(), MAX_PARTICLE_SPEED + MIN_PARTICLE_SPEED) - MIN_PARTICLE_SPEED;

	vect2d direction = { directionX,directionY };

	float transparency = fmod(rand() / 100, 1);

	Particle newParticle = { newPoint, direction, transparency, 1 };

	return newParticle;
}

void removeParticle(Particle* array, int index, int array_length) {
	int i;
	for (i = index; i < array_length - 1; i++) array[i] = array[i + 1];
}