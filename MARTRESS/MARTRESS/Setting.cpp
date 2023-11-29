#include <Windows.h>
#include "Setting.h"
#include "resource.h"

Setting::Setting() {
	onoff = false; 
}
void Setting::run(HDC hdc, HINSTANCE g_hInst) {
	if (onoff) {
		drawHdc = CreateCompatibleDC(hdc);
		drawBmp = LoadBitmap(g_hInst, MAKEINTRESOURCE(SETTING_OFF));
		SelectObject(drawHdc, drawBmp);
		BitBlt(hdc, 0, 0, 1152, 864, drawHdc, 0, 0, SRCCOPY);
		
	}
	else {
		drawHdc = CreateCompatibleDC(hdc);
		drawBmp = LoadBitmap(g_hInst, MAKEINTRESOURCE(SETTING_ON));
		SelectObject(drawHdc, drawBmp);
		BitBlt(hdc, 0, 0, 1152, 864, drawHdc, 0, 0, SRCCOPY);
	}
}
bool Setting::setImg(LPARAM lParam) {
	mx = LOWORD(lParam);
	my = HIWORD(lParam);
	if (mx >= 890 && mx <= 1055 && my >= 680 && my <= 730)
		return false;
	if (!onoff)
		res = sqrt(pow((mx - 835), 2) + pow((my - 415), 2));
	else
		res = sqrt(pow((mx - 760), 2) + pow((my - 415), 2));
	if (res <= 30) {
		if (onoff) {
			onoff = false;
			sndPlaySound("backgroundmusic.wav", SND_ASYNC);
		}

		else {
			onoff = true;
			sndPlaySound(NULL, SND_ASYNC);
		}
	}
	return true;
}