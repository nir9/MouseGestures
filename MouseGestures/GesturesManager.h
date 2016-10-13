#ifndef NIR_GESTURES
#define NIR_GESTURES
#include <Windows.h>
#include <stdio.h>

void RegisterPoint(POINT* p);
BOOL IsGesture();
int GetGestureDirection();
#endif