#include <Windows.h>
#include <stdio.h>
#include "Keyboard.h"

//#define GESTURE_DISTANCE 400
#define GESTURE_DISTANCE 350

/* Last mouse point */
POINT pLast;
/* Initial point x axis */
long initial_x = 0;
/* Direction of gesture (0 is not started) */
int dir = 0;

/* Get direction given two points, if not part of gesture return 0 */
int GetDirection(POINT* p1, POINT* p2)
{
	if (abs(p1->y - p2->y) < 3) {
		if (p2->x < p1->x) {
			return RIGHT;
		}
		else {
			return LEFT;
		}
	}
	else if (abs(p1->y - p2->y) < 17 && p2->x < p1->x) {
		return MINIMIZE;
	}

	return 0;
}

void RegisterPoint(POINT* p)
{
	if (dir == 0) {
		initial_x = p->x;
		dir = 2;
	}
	else {
		int new_dir = GetDirection(p, &pLast);

		if (new_dir != dir && dir != 2) {
			dir = 0;
		}
		else {
			dir = new_dir;
		}
	}

	pLast = *p;
}

BOOL IsGesture()
{
	if (abs(pLast.x - initial_x) >= GESTURE_DISTANCE) {
		dir = 0;
		return TRUE;
	}
	return FALSE;
}

int GetGestureDirection()
{
	return dir;
}