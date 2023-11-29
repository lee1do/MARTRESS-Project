#include <Windows.h>
#include "MainMenu.h"
#include "resource.h"

MainMenu::MainMenu() {
	for (int i = 0; i < 4; i++)
		img[i] = false;
}
void MainMenu::run(HDC hdc, HINSTANCE g_hInst) {
	drawHdc = CreateCompatibleDC(hdc);
	drawBmp = LoadBitmap(g_hInst, MAKEINTRESOURCE(MAINMENU));
	SelectObject(drawHdc, drawBmp);
	BitBlt(hdc, -10, -10, 1152, 864, drawHdc, 0, 0, SRCCOPY);
	DeleteObject(drawHdc);
	if (img[0]) {
		drawMenu = CreateCompatibleDC(hdc);
		drawMenuBmp = LoadBitmap(g_hInst, MAKEINTRESOURCE(GAMESTART_B));
		SelectObject(drawMenu, drawMenuBmp);
		BitBlt(hdc, 380, 400, 380, 77, drawMenu, 0, 0, SRCCOPY);
		DeleteObject(drawMenu);
	}
	else if (img[1]) {
		drawMenu = CreateCompatibleDC(hdc);
		drawMenuBmp = LoadBitmap(g_hInst, MAKEINTRESOURCE(SETTING_B));
		SelectObject(drawMenu, drawMenuBmp);
		BitBlt(hdc, 380, 485, 380, 77, drawMenu, 0, 0, SRCCOPY);
		DeleteObject(drawMenu);
	}
	else if (img[2]) {
		drawMenu = CreateCompatibleDC(hdc);
		drawMenuBmp = LoadBitmap(g_hInst, MAKEINTRESOURCE(CREDIT_B));
		SelectObject(drawMenu, drawMenuBmp);
		BitBlt(hdc, 380, 565, 380, 77, drawMenu, 0, 0, SRCCOPY);
		DeleteObject(drawMenu);
	}
	else if (img[3]) {
		drawMenu = CreateCompatibleDC(hdc);
		drawMenuBmp = LoadBitmap(g_hInst, MAKEINTRESOURCE(EXITGAME_B));
		SelectObject(drawMenu, drawMenuBmp);
		BitBlt(hdc, 380, 648, 380, 77, drawMenu, 0, 0, SRCCOPY);
		DeleteObject(drawMenu);
	}
}
void MainMenu::checkxy(LPARAM lParam) {
	int mx = LOWORD(lParam);
	int my = HIWORD(lParam);
	if (mx >= 380 && mx <= 760 && my >= 405 && my <= 475)
		img[0] = true;
	else
		img[0] = false;
	if (mx >= 380 && mx <= 760 && my >= 485 && my <= 555)
		img[1] = true;
	else
		img[1] = false;
	if (mx >= 380 && mx <= 760 && my >= 565 && my <= 635)
		img[2] = true;
	else
		img[2] = false;
	if (mx >= 380 && mx <= 760 && my >= 645 && my <= 725)
		img[3] = true;
	else
		img[3] = false;
}
int MainMenu::clickxy(LPARAM lParam) {
	int mx = LOWORD(lParam);
	int my = HIWORD(lParam);
	if (mx >= 380 && mx <= 760 && my >= 405 && my <= 475)
		return S_GAMEPLAY;
	else if (mx >= 380 && mx <= 760 && my >= 485 && my <= 555)
		return S_SETTING;
	else if (mx >= 380 && mx <= 760 && my >= 565 && my <= 635)
		return S_CREDIT;
	else if (mx >= 380 && mx <= 760 && my >= 645 && my <= 725)
		return S_EXITGAME;
	else
		return -1;
}