
#include "Bullet.h"


void drawBullet(Bullet bullet) {
	//draw dot
	if (bullet.chaser) {
		glColor3f(0.7, 0.2, 0.7);
		glPointSize(8.0f);
	}
	else {
		glColor3f(1.0, 1.0, 0.0);
		glPointSize(5.0f);
	}
	glBegin(GL_POINTS);
	glVertex2f(bullet.transform.position.x, bullet.transform.position.y);
	glEnd();
}

Bullet moveBullet(Bullet bullet, float dt, point2d chasePoint, int closestIndex) {
	if (bullet.chaser && closestIndex != -1) {
		bullet.movingDirection.x = chasePoint.x - bullet.transform.position.x;
		bullet.movingDirection.y = chasePoint.y - bullet.transform.position.y;
		if (fabs(bullet.movingDirection.x) > fabs(bullet.movingDirection.y)) {
			bullet.movingDirection.y /= fabs(bullet.movingDirection.x);
			bullet.movingDirection.x /= fabs(bullet.movingDirection.x);
		}
		else {
			bullet.movingDirection.x /= fabs(bullet.movingDirection.y);
			bullet.movingDirection.y /= fabs(bullet.movingDirection.y);
		}
		bullet.movingDirection.x *= BULLET_SPEED;
		bullet.movingDirection.y *= BULLET_SPEED;

	}

	float newBulPosX = bullet.transform.position.x + (bullet.movingDirection.x * dt);
	float newBulPosY = bullet.transform.position.y + (bullet.movingDirection.y * dt);
	point2d newBulPos = { newBulPosX ,newBulPosY };
	bullet.transform.position = newBulPos;
	bullet.hitCircle.pos = bullet.transform.position;
	return bullet;
}

Bullet createBullet(Ship ship) {
	float bulletX = circlePos(0 + ship.transform.rotation, ship.transform.scale.x * 1.2, 1) + ship.transform.position.x;
	float bulletY = circlePos(0 + ship.transform.rotation, ship.transform.scale.y * 1.2, 0) + ship.transform.position.y;
	float bulletRot = ship.transform.rotation;

	transform2d newTransform = { {bulletX,bulletY}, bulletRot, {.05,.05} };

	float directionX = circlePos(ship.transform.rotation, BULLET_SPEED, 1);
	float directionY = circlePos(ship.transform.rotation, BULLET_SPEED, 0);

	vect2d direction = { directionX,directionY };

	boolean isChaser = 0;

	if (ship.gunMode == 1) {
		isChaser = 1;
	}

	Bullet newBullet = { newTransform, direction, {{bulletX,bulletY},.01}, 1 , isChaser };

	return newBullet;
}

void removeBullet(Bullet* array, int index, int array_length) {
	int i;
	for (i = index; i < array_length - 1; i++) array[i] = array[i + 1];
}