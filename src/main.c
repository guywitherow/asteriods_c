
#include "GlutHeaders.h"
#include "Ship.h"
#include "GenericTypes.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Particle.h"

typedef struct {
	boolean left;
	boolean right;
	boolean forward;
	boolean fire;
	boolean switchGun;
} heldKeys;


#define FIRE_RATE .2
#define FIRE_RATE_CHASER 1.0
#define NEXT_ROUND_TIMER 5.00

float g_last_time = 0.0;
float lastRot = 0.0;
float speedTimer = 0.0;
float roundTimer = 3.0;
float totalTimer = 0.0;
float endGameTimer = 0.0;
int score = 0;
int roundCounter = 1;

boolean switchGuns = 0;
boolean holdingSwitch = 0;

//0 = first time, 1 = death, 2 = normal play
int gameState = 0;

float lastFired = 0.0;

Bullet bullets[100];
int numOfBullets = 0;

Asteroid asteroids[100];
int numOfAsteroids = 0;

Particle particles[100];
int numOfParticles = 0;

heldKeys currentHeldKeys = { 0,0,0,0 };
heldKeys lastHeldKeys;

Ship ship = {
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
	0
};

/// <summary>
/// Handles the rest of the initalisation
/// </summary>
void init() {
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Asteroids - s3783428");
	glutFullScreen();
	glMatrixMode(GL_PROJECTION);
	glOrtho(-8.0, 8.0, -4.5, 4.5, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}


void renderHUD() {

	if (gameState != 2) {
		if (gameState == 0) {
			glColor3f(1.0, 1.0, 1.0);
			glRasterPos2f(-.8, .4);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, "Press Any Key to Continue...");
		}
		else {
			glColor3f(1.0, 1.0, 1.0);
			glRasterPos2f(-.5, .55);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, "Game Over, Man!");
			
			glColor3f(1.0, 1.0, 1.0);
			glRasterPos2f(-.8, .4);
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, "Press Any Key to Continue...");
		}
	}

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(-6, 4);
	char scoreString[20];
	snprintf(scoreString, 20, "%d", score);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, scoreString);

	char timeString[20];

	snprintf(timeString, 20, "%02.0f:%02.2f", roundf(totalTimer / 60), fmod(totalTimer,60.00));
	glRasterPos2f(6, 4);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, timeString);
}

/// <summary>
/// Render Function
/// </summary>
void renderFrame() {


	renderHUD();

	GLfloat arenaPoints[4][3] = { {4,4,0},
								{-4,4,0} ,
								{-4,-4,0} ,
								{4,-4,0} };


	point2d warningLines = isInsideBox(ship.warningCollision, 4, 4);

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	//top
	if (warningLines.y == 1) {
		glVertex3fv(arenaPoints[0]);
		glVertex3fv(arenaPoints[1]);
	}
	//left
	if (warningLines.x == -1) {
		glVertex3fv(arenaPoints[1]);
		glVertex3fv(arenaPoints[2]);
	}
	//bottom
	if (warningLines.y == -1) {
		glVertex3fv(arenaPoints[2]);
		glVertex3fv(arenaPoints[3]);
	}
	//right
	if (warningLines.x == 1) {
		glVertex3fv(arenaPoints[3]);
		glVertex3fv(arenaPoints[0]);
	}

	glEnd();

	//arena draw
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; i++) {
		glVertex3fv(arenaPoints[i]);
	}
	glEnd();

	drawShip(ship);

	for (int i = 0; i < numOfBullets; i++) {
		if (bullets[i].isLive) {
			drawBullet(bullets[i]);
		}
	}

	for (int i = 0; i < numOfAsteroids; i++) {
		if (asteroids[i].isLive) {
			drawAsteroid(asteroids[i]);
		}
	}
}


void resetGame() {
	Ship resetShip = createShip();
	ship = resetShip;

	for (int i = 0; i < 100; i++) {
		Bullet noBullet = bullets[0];
		noBullet.transform.position.x = 1000;
		noBullet.transform.position.y = 1000;
		noBullet.isLive = 0;
		bullets[i] = noBullet;
	}

	numOfBullets = 0;

	for (int i = 0; i < 100; i++) {
		Asteroid noAsteroid = createAsteroid(ship);
		noAsteroid.transform.position.x = 1000;
		noAsteroid.transform.position.y = 1000;
		noAsteroid.isLive = 0;
		noAsteroid.bounceState = Outside;
		asteroids[i] = noAsteroid;
	}
	numOfAsteroids = 0;

	roundCounter = 1;
	roundTimer = 3.00;

	g_last_time = 0.0;
	lastRot = 0.0;
	speedTimer = 0.0;
	roundTimer = 3.0;
	roundCounter = 1;
	totalTimer = 0.0;
	endGameTimer = 0.0;

	score = 0;

	switchGuns = 0;

	gameState = 1;

	lastFired = 0.0;

	numOfAsteroids = 0;

	numOfParticles = 0;

	currentHeldKeys.fire = 0;
	currentHeldKeys.left = 0;
	currentHeldKeys.right = 0;
	currentHeldKeys.forward = 0;
	currentHeldKeys.switchGun = 0;
	lastHeldKeys;
}


/// <summary>
/// Display Function
/// </summary>
void onDisplay() {
	//deep space blue :)
	glClearColor(0,0,.1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	renderFrame();

	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		printf("display: %s\n", gluErrorString(err));
	}
	glutSwapBuffers();
}


void onMouseClick(int button, int button_state, int x, int y) {
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (button_state == GLUT_DOWN) {
			ship.firing = 1;
		}
		else {
			ship.firing = 0;
		}
		break;
	}
}


/// <summary>
/// Keyboard Handling Function
/// </summary>
/// <param name="key">ASCII key pressed</param>
/// <param name="x">Mouse location X</param>
/// <param name="y">Mouse location Y</param>
void onKeyPress(unsigned char key, int x, int y) {
	switch (key)
	{
	case 27:
	case 'q':
		exit(EXIT_SUCCESS);
		break;

	case 'd':
		currentHeldKeys.right = 1;
		break;

	case 'a':
		currentHeldKeys.left = 1;
		break;

	case 'w':
		currentHeldKeys.forward = 1;
		break;

	case ' ':
		currentHeldKeys.fire = 1;
		break;

	case 'z':
		currentHeldKeys.switchGun = 1;
		if (!holdingSwitch) {
			switchGuns = 1;
		}
		holdingSwitch = 1;

	default:
		break;
	}
}


void onKeyUp(unsigned char key, int x, int y) {
	
	switch (key)
	{
	case 27:
	case 'q':
		exit(EXIT_SUCCESS);
		break;

	case 'd':
		currentHeldKeys.right = 0;
		break;

	case 'a':
		currentHeldKeys.left = 0;
		break;

	case 'w':
		currentHeldKeys.forward = 0;
		break;

	case ' ':
		currentHeldKeys.fire = 0;
		break;

	case 'z':
		currentHeldKeys.switchGun = 0;
		holdingSwitch = 0;
		
	default:
		break;
	}
}


void generateExplosion(float x, float y) {

}


void handleCollisions() {
	
	//if the ship hits the arena, game over
	if ((fabs(ship.transform.position.x) + ship.transform.scale.x >= 4 || 
		fabs(ship.transform.position.y) + ship.transform.scale.y >= 4) &&
		ship.isLive) {
		gameState = 1;
		ship.isLive = 0;
		endGameTimer = 0.0;
	}
	for (int i = 0; i < numOfAsteroids;i++) {
		
		//if the ship hits an asteroid, game over
		/*
		if (detectOverlap(ship.hitCircle, asteroids[i].hitCircle)) {
			gameState = 1;
			ship.isLive = 0;
			endGameTimer = 0.0;
		}*/
		
		if (asteroids[i].isLive) {
			//check for bullet collision
			for (int j = 0; j < numOfBullets; j++) {


				if (bullets[j].isLive && detectOverlap(asteroids[i].hitCircle, bullets[j].hitCircle)) {
					//generateExplosion(asteroids[i].transform.position.x, asteroids[i].transform.position.y);

					bullets[j].transform.position.x = 1000;
					bullets[j].isLive = 0;
					
					//bullets destroyed the asteroid
					if (--asteroids[i].HP == 0) {
						score++;
						asteroids[i].isLive = 0;
						removeAsteroid(asteroids, i, numOfAsteroids);
						numOfAsteroids--;
						i--;
						if (numOfAsteroids <= 0) {
							numOfAsteroids = 0;
						}
						if (i <= 0) {
							i = 0;
						}
						j = numOfBullets + 100;
					}
				}
			}



			point2d hitEdge = isInsideBox(asteroids[i].hitCircle, 4, 4);

			//if we are in the range to hit either the x or y bound of the arena
			if ((hitEdge.x != 0 || hitEdge.y != 0)) {
				
				printf("%i, %i", hitEdge.x, hitEdge.y);

				//this has already crossed the boundary once
				if (asteroids[i].bounceState == Inside) {
					printf("WHY WE NO BOUNCE");
					if (hitEdge.x != 0) {
						asteroids[i].movingDirection.x *= -1;
					}
					else {
						asteroids[i].movingDirection.y *= -1;
					}
				}

				//first time crossing the edge, so we'll mark it as such
				else if (asteroids[i].bounceState == Outside) {
					printf("TOUCHING\n");
					asteroids[i].bounceState = Touching;
				}
				
			}
			else {
				if (asteroids[i].bounceState == Touching) {
					printf("MOVING INSIDE\n");
					asteroids[i].bounceState = Inside;

				}
			}
		}
	}
}


void updateGame(float dt) {

	totalTimer += dt;
	endGameTimer += dt;

	if (gameState != 2 && endGameTimer > 1) {
		if (currentHeldKeys.fire || currentHeldKeys.forward || currentHeldKeys.left || currentHeldKeys.right || currentHeldKeys.switchGun) {
			resetGame();
			gameState = 2;
		}
	}
	else {
		if (ship.isLive) {
			//////////HANDLE ROTATION
			float rotDirection = 0;
			//just left held
			if (currentHeldKeys.left && !currentHeldKeys.right) {
				rotDirection = -1;
			}
			//just right held
			else if (!currentHeldKeys.left && currentHeldKeys.right) {
				rotDirection = 1;
			}
			//neither held
			else if (!currentHeldKeys.left && !currentHeldKeys.right) {
				rotDirection = 0;
			}
			else if (currentHeldKeys.left && currentHeldKeys.right) {
				rotDirection = lastRot;
			}

			lastRot = rotDirection;
			lastHeldKeys = currentHeldKeys;

			ship = rotShip(ship, rotDirection, dt);



			//////////HANDLE MOVE FORWARD

			if (currentHeldKeys.forward) {
				speedTimer += dt;
				if (speedTimer > .3) {
					speedTimer = .3;
				}
				ship = moveShip(ship, dt, speedTimer);
			}
			else if (speedTimer != 0) {
				speedTimer -= dt;
				if (speedTimer < 0) {
					speedTimer = 0;
				}
				ship = moveShip(ship, dt, speedTimer);
			}
		}

		

		if (currentHeldKeys.switchGun && switchGuns) {
			printf("gunMode\n");
			switchGuns = 0;
			if (ship.gunMode == 1) {
				printf("Normal Gun\n");
				lastFired = 0;
				ship.gunMode = 0;
			}
			else {
				printf("Chasers!\n");
				lastFired = 0;
				ship.gunMode = 1;
			}
		}


		if (ship.firing && ship.isLive && ((ship.gunMode == 0 && lastFired > FIRE_RATE) || (ship.gunMode == 1 && lastFired > FIRE_RATE_CHASER))) {
			lastFired = 0;

			Bullet newBullet = createBullet(ship);
			if (numOfBullets >= 100) {
				numOfBullets = 0;
			}
			bullets[numOfBullets++] = newBullet;
		}

		handleCollisions();
		/////HANDLE ROUND TIMER
		roundTimer += dt;
		if (roundTimer > NEXT_ROUND_TIMER) {
			roundTimer = 0;
			for (int i = 0; i < roundCounter; i++) {
				Asteroid newAsteroid = createAsteroid(ship);
				if (numOfAsteroids >= 100) {
					numOfAsteroids = 0;
				}
				asteroids[numOfAsteroids++] = newAsteroid;
			}

			roundCounter++;
		}

		//////////HANDLE BULLET MOVE AND UPDATE
		for (int i = 0; i < numOfBullets; i++) {
			if (bullets[i].isLive == 1) {
				int closestIndex = -1;
				float closestDistance = 500.00;
				if (bullets[i].chaser && numOfAsteroids > 0) {
					for (int j = 0; j < numOfAsteroids; j++) {

						float xDiff = asteroids[j].transform.position.x - bullets[i].transform.position.x;
						float yDiff = asteroids[j].transform.position.y - bullets[i].transform.position.y;

						float distance = sqrt((xDiff * xDiff) + (yDiff * yDiff));

						if (distance < closestDistance) {
							closestDistance = distance;
							closestIndex = j;
						}
					}
				}

				bullets[i] = moveBullet(bullets[i], dt, asteroids[closestIndex].transform.position, closestIndex);
				if (fabs(bullets[i].transform.position.x) >= 4 || fabs(bullets[i].transform.position.y) >= 4) {
					bullets[i].isLive = 0;
					removeBullet(bullets, i, numOfBullets);
					numOfBullets--;
					i--;
					if (numOfBullets <= 0) {
						numOfBullets = 0;
					}
					if (i <= 0) {
						i = 0;
					}
				}
			}
		}

		//////////HANDLE ASTEROID MOVE AND UPDATE
		for (int i = 0; i < numOfAsteroids; i++) {
			if (asteroids[i].isLive == 1) {
				asteroids[i] = moveAsteroid(asteroids[i], dt);
				if (fabs(asteroids[i].transform.position.x) >= 10 || fabs(asteroids[i].transform.position.y) >= 10) {
					asteroids[i].isLive = 0;
					removeAsteroid(asteroids, i, numOfAsteroids);
					printf("removing asteroid%i\n", i);
					numOfAsteroids--;
					i--;
					if (numOfAsteroids <= 0) {
						numOfAsteroids = 0;
					}
					if (i <= 0) {
						i = 0;
					}
				}
			}
		}
	}
	

}


/// <summary>
/// Idle Function
/// </summary>
void onIdle() {
	float cur_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	float dt = cur_time - g_last_time;
	lastFired += dt;
	updateGame(dt);
	g_last_time = cur_time;
	glutPostRedisplay();
}


/// <summary>
/// Main Loop
/// </summary>
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	init();
	glutKeyboardFunc(onKeyPress);
	glutKeyboardUpFunc(onKeyUp);
	glutMouseFunc(onMouseClick);
	glutDisplayFunc(onDisplay);
	glutIdleFunc(onIdle);
	glutMainLoop();
	g_last_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	return (EXIT_SUCCESS);
}
