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

	transform2d newTransform = { {startingX,startingY},0,{1,1} };

	/*
	
	typedef struct {
		transform2d transform;
		vect2d movingDirection;
		collCircle hitCircle;
		boolean isLive;
	} Asteroid;
	
	*/



	//define direction
	float moveX = ship.transform.position.x - startingX;
	float moveY = ship.transform.position.y - startingY;

	//random speed
	float randomSpeed = fmod(rand(), MAX_SPEED - MIN_SPEED) + MIN_SPEED;

	//normalise and scale speed
	moveX = moveX * (2 / randomSpeed);
	moveY = moveY * (2 / randomSpeed);

	vect2d moveDir = { moveX,moveY };

	Asteroid newAsteroid = { newTransform, moveDir, {{0,0},1}, 1};

	printf("Created Asteroid: Details:\nDirection: %f %f\n Pos&Deg: %f %f %f\nShip Pos: %f %f\n",
		moveX, moveY, startingX, startingY, randomDegree, ship.transform.position.x, ship.transform.position.y);

	return newAsteroid;
}

Asteroid moveAsteroid(Asteroid asteroid, float dt) {
	float newAsteroidPosX = asteroid.transform.position.x + (asteroid.movingDirection.x * dt);
	float newAsteroidPosY = asteroid.transform.position.y + (asteroid.movingDirection.y * dt);
	point2d newAsteroidPos = { newAsteroidPosX ,newAsteroidPosY };

	asteroid.transform.position = newAsteroidPos;
	asteroid.hitCircle.pos = asteroid.transform.position;

	return asteroid;
}

void drawAsteroid(Asteroid asteroid) {
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < CIRCLE_POINTS; i++) {
		float pointX = asteroid.transform.position.x + circlePos((360 / CIRCLE_POINTS) * i, .25, 1);
		float pointY = asteroid.transform.position.y + circlePos((360 / CIRCLE_POINTS) * i, .25, 0);
		glVertex2f(pointX,pointY);
	}

	glEnd();
}