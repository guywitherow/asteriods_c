#include "Ship.h"


void drawShip(Ship ship) {
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

	GLfloat shipPoints[4][2] = { {ship.transform.position.x, 
									ship.transform.position.y},
								 {circlePos(220 + ship.transform.rotation,ship.transform.scale.x,1) + ship.transform.position.x, 
									circlePos(220 + ship.transform.rotation,ship.transform.scale.y,0) + ship.transform.position.y},
								 {circlePos(0 + ship.transform.rotation,ship.transform.scale.x,1) + ship.transform.position.x,
									circlePos(0 + ship.transform.rotation,ship.transform.scale.y,0) + ship.transform.position.y},
								 {circlePos(140 + ship.transform.rotation,ship.transform.scale.x,1) + ship.transform.position.x,
									circlePos(140 + ship.transform.rotation,ship.transform.scale.y,0) + ship.transform.position.y}};

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

	float gunCenterX = circlePos(0 + ship.transform.rotation, ship.transform.scale.x, 1) + ship.transform.position.x;
	float gunCenterY = circlePos(0 + ship.transform.rotation, ship.transform.scale.y, 0) + ship.transform.position.y;

	float gunChange = 0;
	if (ship.gunMode == 1) {
		gunChange = .1;
	}

	GLfloat gunPoints[3][2] = {{circlePos(0 + ship.transform.rotation,ship.transform.scale.x * .2, 1 + gunChange) + gunCenterX,
								circlePos(0 + ship.transform.rotation,ship.transform.scale.y * .2,0 + gunChange) + gunCenterY},
								{circlePos(120 + ship.transform.rotation,ship.transform.scale.x * .2, 1) + gunCenterX,
								circlePos(120 + ship.transform.rotation,ship.transform.scale.y * .2,0) + gunCenterY},
								{circlePos(240 + ship.transform.rotation,ship.transform.scale.x * .2, 1) + gunCenterX,
								circlePos(240 + ship.transform.rotation,ship.transform.scale.y * .2,0) + gunCenterY}};

	

	//draw gun
	if (ship.gunMode == 0) {
		glColor3f(1.0, 1.0, 1.0);
	}
	else if (ship.gunMode == 1) {
		glColor3f(0.3, 0.1, 0.1);
	}
	
	glBegin(GL_POLYGON);

	for (int i = 0; i < 3; i++) {
		glVertex2fv(gunPoints[i]);
	}

	glEnd();

}

Ship moveShip(Ship ship, float dt, float speedAmount) {

	float newShipPosX = ship.transform.position.x + circlePos(ship.transform.rotation, ship.speed.x * dt * (speedAmount * 3), 1);
	float newShipPosY = ship.transform.position.y + circlePos(ship.transform.rotation, ship.speed.y * dt * (speedAmount * 3), 0);
	point2d newShipPos = { newShipPosX ,newShipPosY };
	ship.transform.position = newShipPos;

	ship.warningCollision.pos = ship.transform.position;
	ship.hitCircle.pos = ship.transform.position;

	return ship;
}

Ship rotShip(Ship ship, float rotDirection, float dt) {
	float newShipRot = fmod(ship.transform.rotation + (rotDirection * SHIP_ROT_SPEED * dt),360);
	ship.transform.rotation = newShipRot;
	return ship;
}


Ship createShip() {
	Ship newShip = {
		//transform
		{
			//pos
			{0.0, 0.0},
				//rot
				0,
				//scale
			{ .2, .2 }
		},
		//speed
		{ 2, 2 },
		//is firing
		0,
		//col circle 1 (warning)
		{ { 0,0 }, 1.5 },
		//col circle 2 (hit)
		{ { 0,0 }, .1 },
		0,
		1
	};

	return newShip;
}