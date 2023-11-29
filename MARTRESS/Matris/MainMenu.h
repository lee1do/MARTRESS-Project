#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H
#include <Windows.h>
#include "resource.h"

class MainMenu{
private:
	HDC drawHdc, drawMenu, hdc;
	HBITMAP drawBmp, drawMenuBmp;
	HINSTANCE g_hInst;
	bool img[4];
public:
	MainMenu();
	void run(HDC hdc, HINSTANCE g_hInst);
	void checkxy(LPARAM lParam);
	int clickxy(LPARAM lParam);
};

#endif