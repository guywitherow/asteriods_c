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
point2d isInsideBox(collCircle circle, float borderXPos, float borderYPos) {
	int isNearX = 0;
	int isNearY = 0;
	
	//all logic can be simplified with these values
	float circleX = fabs(circle.pos.x);
	float circleY = fabs(circle.pos.y);
	float radius = circle.radius;
	borderXPos = fabs(borderXPos);
	borderYPos = fabs(borderYPos);
	
	if (circleX - radius < borderXPos && circleY - radius < borderYPos) {
		if (circleX + radius > borderXPos) {
			isNearX = 1;
		}
		if (circleY + radius > borderYPos) {
			isNearY = 1;
		}
	}

	point2d returnPoint = { isNearX, isNearY };

	return returnPoint;
}