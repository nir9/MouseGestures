#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "Keyboard.h"
#include "GesturesManager.h"

#define SHOW_WINDOW TRUE

BOOL closed = FALSE;

void MinimizeWindow()
{
	PressKeyCombo(ALT, SPACE);
	PressKey(78);
}
void MoveWindow(int dir)
{
	PressKeyCombo(WINKEY, dir);
}

LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MSLLHOOKSTRUCT* p = (MSLLHOOKSTRUCT*)lParam;
	POINT coords = p->pt;
	//printf("X: %d, Y: %d\n", coords.x, coords.y);
	RegisterPoint(&coords);

	int dir = GetGestureDirection();
	if (IsGesture() && !closed && dir != 0) {
		printf("Dir %d\n", dir);
		puts("gesture recognized!!!!");

		if (dir == MINIMIZE) {
			MinimizeWindow();
		}
		else {
			MoveWindow(dir);
		}
	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

HHOOK mouse_hook;
void main()
{
	if(!SHOW_WINDOW) {
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	}

	mouse_hook = SetWindowsHookEx(WH_MOUSE_LL, HookProc, GetModuleHandle(0), 0);
	if (mouse_hook == 0) {
		printf("Set Hook Failed LE: %d", GetLastError());
	}

	MSG msg;
	while (true) {
		GetMessage(&msg, nullptr, 0, 0);
		DispatchMessage(&msg);
	}
}