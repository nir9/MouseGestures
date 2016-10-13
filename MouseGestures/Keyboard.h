#ifndef NIR_KEYBOARD
#define NIR_KEYBOARD

#include <stdio.h>
#include <Windows.h>

#define ALT 164
#define SPACE 32
#define WINKEY 91
#define LEFT 37
#define RIGHT 39
#define MINIMIZE 3 // maybe move from here..

void PressKey(unsigned short key);
void PressKeyCombo(unsigned short key1, unsigned short key2);

#endif