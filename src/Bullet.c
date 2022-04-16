
#include "Bullet.h"
#include "Ship.h"

void drawBullet(Bullet bullet) {
	//draw dot
	glColor3f(1.0, 1.0, 0.0);
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glVertex2f(bullet.transform.position.x, bullet.transform.position.y);
	glEnd();
}

Bullet moveBullet(Bullet bullet, float dt) {
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

	Bullet newBullet = { newTransform, direction, {{0,0},.2}, 1 };

	return newBullet;
}

void removeBullet(Bullet* array, int index, int array_length) {
	int i;
	for (i = index; i < array_length - 1; i++) array[i] = array[i + 1];
}