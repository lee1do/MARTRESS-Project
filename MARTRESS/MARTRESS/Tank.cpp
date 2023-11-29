#include <math.h>
#include "Tank.h"
#include "resource.h"

#define pi 3.14159265359

void Tank::push_Right()
{
	if (right_MoveSwitch)
	{
		if (!(10 < myPos_x && myPos_x < 1142))
			myPos_x -= 2;
		Fuel--;
		myPos_x += 1;
	}
}
void Tank::push_Left()
{
	if (left_MoveSwitch)
	{
		if (!(10 < myPos_x && myPos_x < 1142))
			myPos_x += 2;
		Fuel--;
		myPos_x -= 1;
	}
}
void Tank::push_Up()
{

	if (barrelUp_MoveSwitch)
		if (Team)
			Degree += (1. / 180.)*pi;
		else
			Degree -= (1. / 180.)*pi;

}
void Tank::push_Down()
{

	if (barrelDown_MoveSwitch)
		if (Team)
			Degree -= (1. / 180.)*pi;
		else
			Degree += (1. / 180.)*pi;


}
void Tank::push_Space()
{
	static int GageVelo = 40;
	static bool GageSwitch = 1;
	if (!shot_Switch)
	{
		myMissile.Velocity += GageVelo;
		if (myMissile.Velocity >= 2000. && GageSwitch)
		{
			GageVelo *= -1;
			GageSwitch = 0;
		}
		else if (myMissile.Velocity <= 0. && !GageSwitch)
		{
			GageVelo *= -1;
			GageSwitch = 1;
		}
	}

}
void Tank::Shot()
{
	if (!shot_Switch)
	{
		switch (myMissile.missileMode)
		{
		case 1://일반 미사일
			myMissile.Damage = 800;
			myMissile.Range = 90;
			break;
		case 2://폭탄 강화
			myMissile.Damage = 1500;
			myMissile.Range = 150;
			skills_Limit[0]--;
			break;
		case 3://두번 발사
			myMissile.Damage = 800;
			myMissile.Range = 90;
			skills_Limit[1]--;
			break;
		case 4://회복
			myMissile.Damage = 0;
			myMissile.Range = 50;
			for (int c = 0; c < myMissile.Velocity / 2.5; c++) {
				if (Life > 2000)
					break;
				Life++;
			}
			skills_Limit[2]--;
			break;
		}
		myMissile.missilePos_x = myPos_x;
		myMissile.missilePos_y = myPos_y-20;
		myMissile.startPos_x = myPos_x;
		myMissile.startPos_y = myPos_y - 20;
		if (Team)
			myMissile.common_Differ = myMissile.Velocity / 200. + 4.;
		else
			myMissile.common_Differ = -(myMissile.Velocity / 200. + 4.);
		myMissile.Degree = Degree;
		shot_Switch = 1;
	}
}

Tank::Tank(bool Team, int Character, int myPos_x, int Degree, int Life)
{
	this->Team = Team;
	this->Character = Character;
	this->myPos_x = myPos_x;
	this->myPos_y = 300;
	this->Life = Life;
	this->Fuel = 70;
	this->myTime = 1000;
	this->skills_Limit[0] = { 1 }; skills_Limit[1] = { 1 }; skills_Limit[2] = { 1 };
	if (Team)
		this->Degree = (Degree / 180.)*pi;
	else
		this->Degree = ((180 - Degree) / 180.)*pi;
	right_MoveSwitch = 1;
	left_MoveSwitch = 1;
	down_MoveSwitch = 1;
	barrelUp_MoveSwitch = 1;
	barrelDown_MoveSwitch = 1;
	shot_Switch = 0;
}
void Tank::Draw(HINSTANCE ins, HDC hdc, HDC hdcBackBuf)
{
	HDC TNThdc, HEARThdc, tankHeadHdc,tankBottomHdc;
	HBITMAP TNTbmp, HEARTbmp, tankHeadBmp, tankBottomBmp;
	HBRUSH redBrush, yellowBrush, greenBrush, blackBrush, oBrush;
	redBrush = CreateSolidBrush(RGB(255, 0, 0));
	yellowBrush = CreateSolidBrush(RGB(255, 255, 0));
	greenBrush = CreateSolidBrush(RGB(0, 255, 0));
	blackBrush = CreateSolidBrush(RGB(0, 0, 0));

	TNThdc = CreateCompatibleDC(hdc);
	TNTbmp = LoadBitmap(ins, MAKEINTRESOURCE(TNT));
	SelectObject(TNThdc, TNTbmp);

	HEARThdc = CreateCompatibleDC(hdc);
	HEARTbmp = LoadBitmap(ins, MAKEINTRESOURCE(HEART));
	SelectObject(HEARThdc, HEARTbmp);

	tankHeadHdc = CreateCompatibleDC(hdc);
	tankHeadBmp = LoadBitmap(ins, MAKEINTRESOURCE(TANKH));
	SelectObject(tankHeadHdc, tankHeadBmp);

	tankBottomHdc = CreateCompatibleDC(hdc);
	tankBottomBmp = LoadBitmap(ins, MAKEINTRESOURCE(TANKB));
	SelectObject(tankBottomHdc, tankBottomBmp);

	if (Team)
	{
		oBrush = (HBRUSH)SelectObject(hdcBackBuf, blackBrush);
		for (int i = 7; i > 0; i--)
		{
			Rectangle(hdcBackBuf, myPos_x + (8 * i)*cos(Degree) - 7, myPos_y - (8 * i)*sin(Degree) - 7 - 20, myPos_x + (8 * i)*cos(Degree) + 7, myPos_y - (8 * i)*sin(Degree) + 7 - 20);
		}
		SelectObject(hdcBackBuf, oBrush);

		BitBlt(hdcBackBuf, myPos_x -20, myPos_y-30 -20, 40, 40, tankHeadHdc, 0, 0, SRCCOPY);
		BitBlt(hdcBackBuf, myPos_x - 30, myPos_y +10 - 20, 60, 20, tankBottomHdc, 0, 0, SRCCOPY);

		Rectangle(hdcBackBuf, 370, 703, 380 + myTime * (113. / 1000.), 710);

		switch (myMissile.missileMode) {
		case 1:
			Ellipse(hdcBackBuf, 432 - 10, 755 - 10, 432 + 10, 755 + 10);
			break;
		case 2:
			BitBlt(hdcBackBuf, 422, 745, 30, 30, TNThdc, 0, 0, SRCCOPY);
			break;
		case 3:
			Ellipse(hdcBackBuf, 412 - 10, 755 - 10, 412 + 10, 755 + 10);
			Ellipse(hdcBackBuf, 452 - 10, 755 - 10, 452 + 10, 755 + 10);
			break;
		case 4:
			BitBlt(hdcBackBuf, 422, 745, 30, 30, HEARThdc, 0, 0, SRCCOPY);
			break;
		}

		SelectObject(hdcBackBuf, redBrush);
		for (int i = 7; i > 0; i--)
		{
			Rectangle(hdcBackBuf, 268 + (8 * i)*cos(Degree) - 7, 758 - (8 * i)*sin(Degree) - 7, 268 + (8 * i)*cos(Degree) + 7, 758 - (8 * i)*sin(Degree) + 7);
		}
		SelectObject(hdcBackBuf, blackBrush);
		Rectangle(hdcBackBuf, 268 - 7, 758 - 7, 268 + 7, 758 + 7);
		SelectObject(hdcBackBuf, redBrush);
		Rectangle(hdcBackBuf, 622, 718, 622 + Life * (341. / 2000.), 675);
		SelectObject(hdcBackBuf, greenBrush);
		Rectangle(hdcBackBuf, 622, 768, 622 + myMissile.Velocity*(341. / 2000.), 725);
		SelectObject(hdcBackBuf, yellowBrush);
		Rectangle(hdcBackBuf, 622, 818, 622 + Fuel * (341. / 70.), 775);
		SelectObject(hdcBackBuf, oBrush);

	}
	else
	{
		oBrush = (HBRUSH)SelectObject(hdcBackBuf, blackBrush);
		for (int i = 7; i > 0; i--)
		{
			Rectangle(hdcBackBuf, myPos_x + (8 * i)*cos(Degree) - 7, myPos_y - (8 * i)*sin(Degree) - 7 - 20, myPos_x + (8 * i)*cos(Degree) + 7, myPos_y - (8 * i)*sin(Degree) + 7 - 20);
		}

		SelectObject(hdcBackBuf, oBrush);

		BitBlt(hdcBackBuf, myPos_x - 20, myPos_y - 30 - 20, 40, 40, tankHeadHdc, 0, 0, SRCCOPY);
		BitBlt(hdcBackBuf, myPos_x - 30, myPos_y + 10 - 20, 60, 20, tankBottomHdc, 0, 0, SRCCOPY);

		Rectangle(hdcBackBuf, 370, 703 - 666, 380 + myTime * (113. / 1000.), 710 - 666);

		switch (myMissile.missileMode) {
		case 1:
			Ellipse(hdcBackBuf, 432 - 10, 755-666 - 10, 432 + 10, 755-666 + 10);
			break;
		case 2:
			BitBlt(hdcBackBuf, 422, 745 - 666, 30, 30, TNThdc, 0, 0, SRCCOPY);
			break;
		case 3:
			Ellipse(hdcBackBuf, 412 - 10, 755 - 666 - 10, 412 + 10, 755 - 666 + 10);
			Ellipse(hdcBackBuf, 452 - 10, 755 - 666 - 10, 452 + 10, 755 - 666 + 10);
			break;
		case 4:
			BitBlt(hdcBackBuf, 422, 745 - 666, 30, 30, HEARThdc, 0, 0, SRCCOPY);
			break;
		}

		SelectObject(hdcBackBuf, redBrush);
		for (int i = 7; i > 0; i--)
		{
			Rectangle(hdcBackBuf, 268 + (8 * i)*cos(Degree) - 7, 758 - 666 - (8 * i)*sin(Degree) - 7, 268 + (8 * i)*cos(Degree) + 7, 758 - 666 - (8 * i)*sin(Degree) + 7);
		}
		SelectObject(hdcBackBuf, blackBrush);
		Rectangle(hdcBackBuf, 268 - 7, 758 - 666 - 7, 268 + 7, 758 - 666 + 7);
		SelectObject(hdcBackBuf, redBrush);
		Rectangle(hdcBackBuf, 622, 718 - 666, 622 + Life * (341. / 2000.), 675 - 666);
		SelectObject(hdcBackBuf, greenBrush);
		Rectangle(hdcBackBuf, 622, 768 - 666, 622 + myMissile.Velocity*(341. / 2000.), 725 - 666);
		SelectObject(hdcBackBuf, yellowBrush);
		Rectangle(hdcBackBuf, 622, 818 - 666, 622 + Fuel * (341. / 70.), 775 - 666);
		SelectObject(hdcBackBuf, oBrush);
	}
	DeleteObject(yellowBrush);
	DeleteObject(redBrush);
	DeleteObject(greenBrush);
	DeleteObject(blackBrush);

	DeleteDC(TNThdc);
	DeleteObject(TNTbmp);
	DeleteDC(HEARThdc);
	DeleteObject(HEARTbmp);

	DeleteDC(tankHeadHdc);
	DeleteObject(tankHeadBmp);
	DeleteDC(tankBottomHdc);
	DeleteObject(tankBottomBmp);
}
void Tank::Run(HINSTANCE ins, HDC hdc, HDC hdcBackBuf)
{
	Draw(ins, hdc, hdcBackBuf);
	if (down_MoveSwitch)
		myPos_y += 1;
	if (shot_Switch)
		myMissile.Draw(ins, hdc, hdcBackBuf);
}