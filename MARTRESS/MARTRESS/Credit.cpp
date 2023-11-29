#include <windows.h>
#include "Credit.h"
#include "resource.h"

void Credit::run(HWND hWnd, HDC hdc, HINSTANCE g_hInst) {
	hBGA = LoadBitmap(g_hInst, MAKEINTRESOURCE(CREDIT));
	hdcback = CreateCompatibleDC(hdc);
	hbmMem = hBGA;
	hbmMemOld = (HBITMAP)SelectObject(hdcback, hbmMem);

	BitBlt(hdc, 0, posy, 1152, 2160, hdcback, 0, 0, SRCCOPY);

	SelectObject(hdcback, hbmMemOld);
	DeleteObject(hbmMem);
	DeleteDC(hdcback);
}

void Credit::decreasePosy() {
	posy -= 5;
}
int Credit::getPosy() {
	return posy;
}
void Credit::setPosy(int n) {
	posy = n;
}