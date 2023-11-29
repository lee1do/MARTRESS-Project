#include <iostream>
#include <math.h>
#include "Missile.h"
#include "resource.h"
Missile::Missile()
{
	missileMode = 1;
	Velocity = 40;
	common_Differ = 0;
	Range=100;	//50이상
	Damage=1000;//최대피해량

}
int Missile::Parabola()
{
	double a, b, x, y;
	x = missilePos_x - startPos_x;
	a = (-1)*(1.0 / (Velocity*cos(Degree)*cos(Degree)));
	b = sin(Degree) / cos(Degree);
	y = (-1) *(a*x*x + b * x) + startPos_y;
	return y;
}
void Missile::Draw(HINSTANCE ins,HDC hdc, HDC hdcBackBuf)
{
	switch(missileMode)
	{
	case 1:
		missilePos_x += common_Differ;
		missilePos_y = Parabola();
		Ellipse(hdcBackBuf, missilePos_x - 10, missilePos_y - 10, missilePos_x + 10, missilePos_y + 10);
		break;
	case 2:
		HDC TNThdc;
		HBITMAP TNTbmp;
		TNThdc = CreateCompatibleDC(hdc);
		TNTbmp = LoadBitmap(ins, MAKEINTRESOURCE(TNT));
		SelectObject(TNThdc, TNTbmp);
		missilePos_x += common_Differ;
		missilePos_y = Parabola();
		BitBlt(hdcBackBuf, missilePos_x - 10, missilePos_y - 10, 30, 30, TNThdc, 0, 0, SRCCOPY);
		DeleteDC(TNThdc);
		DeleteObject(TNTbmp);
		break;
	case 3:
		missilePos_x += common_Differ;
		missilePos_y = Parabola();
		Ellipse(hdcBackBuf, missilePos_x - 10, missilePos_y - 10, missilePos_x + 10, missilePos_y + 10);
		break;
	case 4:
		missilePos_x += common_Differ;
		missilePos_y = Parabola();
		break;
	}
	
;
}