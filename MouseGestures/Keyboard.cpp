#include <stdio.h>
#include <Windows.h>

void PressKey(unsigned short key)
{
	INPUT input;
	input.type = INPUT_KEYBOARD;

	input.ki.wVk = key;
	input.ki.wScan = 0;

	// Press Key
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(input));

	// Release Key
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(input));
}

void PressKeyCombo(unsigned short key1, unsigned short key2)
{
	INPUT input;
	input.type = INPUT_KEYBOARD;

	input.ki.wScan = 0;

	// Press Key1
	input.ki.wVk = key1;
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(input));

	// Press Key2
	input.ki.wVk = key2;
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(input));

	// Release Key2
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(input));

	// Release Key1
	input.ki.wVk = key1;
	SendInput(1, &input, sizeof(input));
}