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
