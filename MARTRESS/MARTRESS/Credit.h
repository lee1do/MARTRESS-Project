#pragma once
#include <windows.h>
#include "resource.h"
#include <string>
#ifndef CREDIT_H
#define CREDIT_H

class Credit {
	PAINTSTRUCT ps;
	HDC hdcback;
	HBITMAP hbmMem, hbmMemOld, hBGA;
	int posy;
public:
	void run(HWND hWnd, HDC hdc, HINSTANCE g_hInst);
	void decreasePosy();
	int getPosy();
	void setPosy(int n);
};
#endif