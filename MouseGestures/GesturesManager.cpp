#include <Windows.h>
#include <stdio.h>
#include "Keyboard.h"

// perhaps work with ratio and take into consideration the screen size (height and width)

#define GESTURE_DISTANCE 500

/* Last mouse point */
POINT pLast;
/* Initial point x axis */
long initial_x = 0;
/* Direction of gesture (0 is not started) */
int dir = 0;

int save = 0;


/* Get direction given two points, if not part of gesture return 0 */
int GetDirection(POINT* p1, POINT* p2)
{
	/* Distances */
	int dY = abs(p1->y - p2->y);
	int dX = abs(p1->x - p2->x);

	// Moving window gestures
	if (dY < 1) {
		if (p2->x < p1->x) {
			return RIGHT;
		}
		else {
			return LEFT;
		}
	}

	// Minimize Gesture
	else if (p2->x < p1->x) {
		int deltaY = (p2->y - p1->y);
		int deltaX = (p2->x - p1->x);
		
		int slope = deltaY / deltaX;

		printf("slope %d\n", slope);
		if (slope == -1 || slope == -2) {
			printf("YESSS!!!\n");
			save = 0;
			return MINIMIZE;
		}
		else if (slope == 0)
		{
			if (save == 5) {
				save = 0;
				return 0;
			}
			else {
				save++;
				return MINIMIZE;
			}
		}
	}

	return 0;
}

/* Registers a mouse point */
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

/* Returns true when gesture has been made */
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


/*
To add ratio gestures:
GetMonitorInfo, MonitorFromWindow, GetForegroundWindow
*/