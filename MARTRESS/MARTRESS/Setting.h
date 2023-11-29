#pragma once
#ifndef SETTING_H
#define SETTING_H
#include <Windows.h>
#include <math.h>
#include "resource.h"

class Setting {
private:
	HDC drawHdc;
	HBITMAP drawBmp;
	bool onoff;
	int mx, my;
	double res;
public:
	Setting();
	void run(HDC hdc, HINSTANCE g_hInst);
	bool setImg(LPARAM lParam);
};
#endif