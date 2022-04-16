#include "GenericTypes.h"

float circlePos(float degree, float r, boolean isX) {
	float final = r;
	float degToRad = degree * (PI / 180);
	if (isX) {
		final *= sin(degToRad);
	}
	else {
		final *= cos(degToRad);
	}

	return final;
}

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

	if (fabs(circle.pos.x + (circle.radius * quadrantX)) > limitX && fabs(circle.pos.x - (circle.radius * quadrantX)) < limitX) {
		isNearX = 1 * quadrantX;
	}
	if (fabs(circle.pos.y + (circle.radius * quadrantY)) > limitY && fabs(circle.pos.y - (circle.radius * quadrantY)) < limitY) {
		isNearY = 1 * quadrantY;
	}

	point2d returnPoint = { isNearX, isNearY };

	return returnPoint;
}