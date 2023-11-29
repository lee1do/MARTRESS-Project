#include <windows.h>
#include "Missile.h"

#ifndef TANK_H
#define TANK_H
class Tank
{
public:
	Tank(bool Team,int Character, int myPos_x, int Degree, int Life);
	Missile myMissile;
	//맴버변수
	int    Fuel;
	int    Life;
	int    Character;
	int    myPos_x;
	int    myPos_y;
	int    myTime;
	int		skills_Limit[3];
	bool Team;
	double Degree;
	//맴버함수
	void Draw(HINSTANCE ins, HDC hdc, HDC hdcBackBuf);
	void Shot();
	void Run(HINSTANCE ins, HDC hdc, HDC hdcBackBuf);
	void push_Right();
	void push_Left();
	void push_Up();
	void push_Down();
	void push_Space();
	//스위치들
	bool right_MoveSwitch;
	bool left_MoveSwitch;
	bool down_MoveSwitch;
	bool barrelUp_MoveSwitch;
	bool barrelDown_MoveSwitch;
	bool shot_Switch;
};
#endif