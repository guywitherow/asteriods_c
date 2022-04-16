
#include "Bullet.h"

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
