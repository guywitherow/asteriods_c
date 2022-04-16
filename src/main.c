
#include "GlutHeaders.h"
#include "Ship.h"
#include "GenericTypes.h"
#include "Bullet.h"
#include "Asteroid.h"

typedef struct {
	boolean left;
	boolean right;
	boolean forward;
	boolean fire;
} heldKeys;


#define FIRE_RATE .2
#define BULLET_SPEED 5

float g_last_time = 0.0;
float lastRot = 0.0;
float speedTimer = 0.0;

float lastFired = 0;
Bullet bullets[100];
Asteroid asteroids[100];
int numOfBullets = 0;



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
			{.2, .2}
		},
		//speed
		{2, 2},
		//is firing
		0,
		//col circle 1 (warning)
		{ { 0,0 }, 1.5},
		//col circle 2 (hit)
		{ { 0,0 }, .2}
};

int detectOverlap(collCircle circle1, collCircle circle2) {
	float dx = circle2.pos.x - circle1.pos.x;
	float dy = circle2.pos.y - circle1.pos.y;
	float radii = circle1.radius + circle2.radius;
	if ((radii * radii) <= (dx * dx) + (dy * dy))
	{
		return 0;
	}
	return 1;
}


//returns a point 2d with the co-ordinates representing the lines
// 1 = positive, -1 = negative, 0 = not close to either
point2d detectLineOverlap(collCircle circle, float limitX, float limitY) {

	int isNearX = 0;
	int isNearY = 0;

	float quadrantX = 1;
	float quadrantY = 1;
	if (circle.pos.x < 0) {
		quadrantX = -1;
	}
	if (circle.pos.y < 0) {
		quadrantY = -1;
	}

	if (fabs(circle.pos.x + (circle.radius * quadrantX)) > limitX) {
		isNearX = 1 * quadrantX;
	}
	if (fabs(circle.pos.y + (circle.radius * quadrantY)) > limitY) {
		isNearY = 1 * quadrantY;
	}

	point2d returnPoint = { isNearX, isNearY };

	return returnPoint;
}


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


/// <summary>
/// Render Function
/// </summary>
void renderFrame() {




	GLfloat arenaPoints[4][3] = { {4,4,0},
								{-4,4,0} ,
								{-4,-4,0} ,
								{4,-4,0} };


	point2d warningLines = detectLineOverlap(ship.warningCollision, 4, 4);

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

	for (int i = 0; i < 100; i++) {
		if (bullets[i].isLive) {
			drawBullet(bullets[i]);
		}
	}

	for (int i = 0; i < 100; i++) {
		if (asteroids[i].isLive) {
			drawAsteroid(asteroids[i]);
		}
	}

}


void resetGame() {
	Ship resetShip = {
		//transform
		{
			//pos
			{0.0, 0.0},
			//rot
			0,
			//scale
			{.2, .2}
		},
		//speed
		{2, 2},
		//is firing
		0,
		//col circle 1 (warning)
		{ { 0,0 }, 2.5},
		//col circle 2 (hit)
		{ { 0,0 }, .2}
	};
	ship = resetShip;
	for (int i = 0; i < 100; i++) {
		Bullet noBullet = bullets[0];
		noBullet.transform.position.x = 1000;
		noBullet.transform.position.y = 1000;
		bullets[i] = noBullet;
	}

	for (int i = 0; i < 6; i++) {
		Asteroid newAsteroid = createAsteroid(ship);
		asteroids[i] = newAsteroid;
	}
	
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
	default:
		break;
	}
}


void updateGame(float dt) {
	if (fabs(ship.transform.position.x) + ship.transform.scale.x >= 4 || fabs(ship.transform.position.y) + ship.transform.scale.y >= 4) {
		resetGame();
	}

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

	for (int i = 0; i < 100; i++) {
		if (bullets[i].isLive == 1) {
			bullets[i] = moveBullet(bullets[i], dt);
			if (fabs(bullets[i].transform.position.x) >= 4 || fabs(bullets[i].transform.position.y) >= 4) {
				bullets[i].isLive = 0;
			}
		}
	}

	for (int i = 0; i < 100; i++) {
		if (asteroids[i].isLive == 1) {
			asteroids[i] = moveAsteroid(asteroids[i], dt);
			if (fabs(asteroids[i].transform.position.x) >= 9 || fabs(asteroids[i].transform.position.y) >= 5) {
				bullets[i].isLive = 0;
			}
		}
	}

	if (ship.firing && lastFired > FIRE_RATE) {
		lastFired = 0;

		float bulletX = circlePos(0 + ship.transform.rotation, ship.transform.scale.x * 1.2, 1) + ship.transform.position.x;
		float bulletY = circlePos(0 + ship.transform.rotation, ship.transform.scale.y * 1.2, 0) + ship.transform.position.y;
		float bulletRot = ship.transform.rotation;
		transform2d newTransform = { {bulletX,bulletY}, bulletRot, {.05,.05} };

		float directionX = circlePos(ship.transform.rotation, BULLET_SPEED, 1);
		float directionY = circlePos(ship.transform.rotation, BULLET_SPEED, 0);

		vect2d direction = { directionX,directionY };

		Bullet newBullet = { newTransform, direction, {{0,0},.2}, 1 };
		if (numOfBullets >= 100) {
			numOfBullets = 0;
		}
		bullets[numOfBullets++] = newBullet;
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
