#include "Asteroid.h"

Asteroid createAsteroid(Ship ship) {
	//create at position on surrounding ring
	/*
	  
	  
	   | + radius of asteroid (1)
	   |\
	   |	\   ~8.25
	 2 |		\
	   |___________\
			8
	
	therefore spawning circle should be at radius 9.25
	
	*/
	
	float randomDegree = fmod(rand(),359.99);

	float startingX = circlePos(randomDegree,SPAWNING_RAD,1);
	float startingY = circlePos(randomDegree, SPAWNING_RAD, 0);

	float randomSize = fmod(rand() / 1000.00, MAX_SIZE - MIN_SIZE) + MIN_SIZE;

	//int rounding down
	int HP = (randomSize / .1) - 2;
	if (HP == 0) {
		HP = 1;
	}


	transform2d newTransform = { {startingX,startingY},0,{randomSize,randomSize} };

	//define direction
	float moveX = ship.transform.position.x - startingX;
	float moveY = ship.transform.position.y - startingY;

	//random speed
	float randomSpeed = fmod(rand() / 1000.00, MAX_SPEED - MIN_SPEED) + MIN_SPEED;

	//normalise and scale speed
	moveX = moveX * randomSpeed;
	moveY = moveY * randomSpeed;

	vect2d moveDir = { moveX,moveY };

	int pointCount = (rand() % 6) + 6;
	float spikeSeed = fmod((float)rand() / 10000.00, 0.5) - .25;

	float rotSpeed = fmod(rand() / 1000.00, MAX_SPIN - MIN_SPIN) + MIN_SPIN;

	Asteroid newAsteroid = { newTransform, moveDir, {newTransform.position,randomSize+.05}, 1, 
		pointCount, spikeSeed, rotSpeed, HP, 0, 0};

	

	return newAsteroid;
}

Asteroid moveAsteroid(Asteroid asteroid, float dt) {
	float newAsteroidPosX = asteroid.transform.position.x + (asteroid.movingDirection.x * dt);
	float newAsteroidPosY = asteroid.transform.position.y + (asteroid.movingDirection.y * dt);
	point2d newAsteroidPos = { newAsteroidPosX ,newAsteroidPosY };

	asteroid.transform.position = newAsteroidPos;
	asteroid.hitCircle.pos = asteroid.transform.position;

	asteroid.transform.rotation += asteroid.rotSpeed;

	return asteroid;
}

void drawAsteroid(Asteroid asteroid) {
	float greenAmount = 1.00 / (float)asteroid.HP;
	float redAmount = 1.00 / 10 - (float)asteroid.HP;
	glColor3f(redAmount, greenAmount, 1.0);
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < asteroid.pointCount; i++) {

		float variance = fmod((float)i * asteroid.spikeSeed, VARIANCE) - (VARIANCE/2);

		float pointX = asteroid.transform.position.x + circlePos(((360 / asteroid.pointCount) * i) + asteroid.transform.rotation,
			asteroid.transform.scale.x + variance, 1);
		float pointY = asteroid.transform.position.y + circlePos(((360 / asteroid.pointCount) * i) + asteroid.transform.rotation,
			asteroid.transform.scale.y + variance, 0);
		glVertex2f(pointX,pointY);
	}

	glEnd();
}

void removeAsteroid(Asteroid* array, int index, int array_length) {
	int i;
	for (i = index; i < array_length - 1; i++) array[i] = array[i + 1];
}