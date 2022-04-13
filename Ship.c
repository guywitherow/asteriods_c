#include "Ship.h"

struct Ship {
	GLfloat posX;
	GLfloat posY;
	float size;
	float facing;
	float velocityForward;
	float velocityTurn;
	boolean firing;
};

void drawShip(struct Ship ship) {
	//ship points are placed on a circle as here:
	/*
		o X o
	 o        o
	o          o
	o     X    o
	 o        o
	  X o  o X

	so @ 0deg, 140deg and 220deg (tails are slightly closer than thirds)
	*/

	GLfloat shipPoints[4][2] = { {circlePos(0,ship.size,1) + ship.posX, circlePos(0,ship.size,0) + ship.posY},
								 {circlePos(140,ship.size,1) + ship.posX, circlePos(120,ship.size,0) + ship.posY},
								 {ship.posX, ship.posY},
								 {circlePos(220,ship.size,1) + ship.posX, circlePos(240,ship.size,0) + ship.posY} };
	//draw outline
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; i++) {
		glVertex2fv(shipPoints[i]);
	}
	glEnd();

	//draw fill
	glColor3f(0.3, 0.1, 0.1);
	glBegin(GL_POLYGON);

	for (int i = 0; i < 4; i++) {
		glVertex2fv(shipPoints[i]);
	}

	glEnd();
}