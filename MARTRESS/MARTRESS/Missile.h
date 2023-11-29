#include <windows.h>
#ifndef MISSILE_H
#define MISSILE_H
class Missile
{
public:
	Missile();
	int missilePos_x;
	int missilePos_y;
	int startPos_x;
	int startPos_y;
	int Range=45;
	int Damage;
	int missileMode;
	double Velocity;
	double Degree;
	double common_Differ;
	int Parabola();
	void Draw(HINSTANCE ins, HDC hdc, HDC hdcBackBuf);
};
#endif
