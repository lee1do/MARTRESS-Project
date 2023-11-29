#include <iostream>
#include <math.h>
#include <windows.h>
#include "MARTRISS.h"
#define pi 3.14159265359
double Length(double x1, double y1, double x2, double y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}
void MARTRISS::groundExplosion(HWND hWnd)
{
	int Dp=tankOfThisTurn()->myMissile.missilePos_y;
	if (checkMissile(tankOfThisTurn(), Dp))
	{
		
		double missile_X = tankOfThisTurn()->myMissile.missilePos_x;
		double missile_Y = tankOfThisTurn()->myMissile.missilePos_y;
		double enemy_X = tankOfThisTurn(1)->myPos_x;
		double enemy_Y = tankOfThisTurn(1)->myPos_y;
		double Len = Length(missile_X, missile_Y, enemy_X, enemy_Y);
		if (Len < tankOfThisTurn()->myMissile.Range)
			tankOfThisTurn(1)->Life -= tankOfThisTurn()->myMissile.Damage/(1+(Len/100));
		if (tankOfThisTurn(1)->Life <= 0)
		{
			if (tankOfThisTurn()->Team)
			{
				KillTimer(hWnd, 1);
				MessageBox(hWnd, TEXT("1P ½Â¸®!"), TEXT("Àû ÅÊÅ© ÆÄ±«!!!!"), MB_OK);
				DestroyWindow(hWnd);
			}
			else
			{
				KillTimer(hWnd, 1);
				MessageBox(hWnd, TEXT("2P ½Â¸®!"), TEXT("Àû ÅÊÅ© ÆÄ±«!!!!"), MB_OK);
				DestroyWindow(hWnd);
			}
		}
		for (int y = 0; y < 48; y++)
		{
			for (int x = 0; x < 64; x++)
			{
				if (MAP->MapBlock[y][x])
				{
					if (Length(missile_X, missile_Y, x * 18 - 9, y * 18 - 9) < tankOfThisTurn()->myMissile.Range-50)
					{
						if(MAP->MapBlock[y][x] != 3)
							MAP->MapBlock[y][x] = 0;
					}
				}
			}
		}
		if (tankOfThisTurn()->myMissile.missileMode == 3)
		{
			tankOfThisTurn()->myMissile.missilePos_x = 0;
			tankOfThisTurn()->myMissile.missilePos_y = 0;
			tankOfThisTurn()->myMissile.Velocity = 40;
			tankOfThisTurn()->myMissile.common_Differ = 0;
			tankOfThisTurn()->myMissile.missileMode = 1;
			tankOfThisTurn()->myTime = 1000;
			tankOfThisTurn()->Fuel = 70;
			tankOfThisTurn()->shot_Switch = 0;
		}
		else
		{
			tankOfThisTurn()->myMissile.missilePos_x = 0;
			tankOfThisTurn()->myMissile.missilePos_y = 0;
			tankOfThisTurn()->myMissile.Velocity = 40;
			tankOfThisTurn()->myMissile.common_Differ = 0;
			tankOfThisTurn()->myMissile.missileMode = 1;
			tankOfThisTurn()->myTime = 1000;
			tankOfThisTurn()->Fuel = 70;
			tankOfThisTurn()->shot_Switch = 0;
			Turn = !Turn;
		}
	}
}
void MARTRISS::tankMoveControl(Tank* a)
{
	//¿À¸¥ÂÊ
	if (checkRight(a,a->myPos_x + 1) || a->shot_Switch)
		a->right_MoveSwitch = 0;
	else
		a->right_MoveSwitch = 1;
	//¿ÞÂÊ
	if (checkLeft(a,a->myPos_x - 1) || a->shot_Switch)
		a->left_MoveSwitch = 0;
	else
		a->left_MoveSwitch = 1;
	//¾Æ·¡
	if(checkDown(a, a->myPos_y + 1))
		a->down_MoveSwitch = 0;
	else
		a->down_MoveSwitch = 1;
	//Æ÷½ÅÀ§
	if (checkBarrelUp(a, a->Degree) || a->shot_Switch)
		a->barrelUp_MoveSwitch = 0;
	else
		a->barrelUp_MoveSwitch = 1;
	//Æ÷½Å¾Æ·¡
	if (checkBarrelDown(a, a->Degree) || a->shot_Switch)
		a->barrelDown_MoveSwitch = 0;
	else
		a->barrelDown_MoveSwitch = 1;
}
void MARTRISS::Run(HINSTANCE ins,HDC hdc,HDC hdcBackBuf, HWND hWnd)
{
	if (tankOfThisTurn()->myTime-- < 0)
	{
		tankOfThisTurn()->myTime = 1000;
		Turn = !Turn;
	}
	MAP->Run(ins, hdc, hdcBackBuf);
	ME->Run(ins,hdc,hdcBackBuf);
	ENEMY->Run(ins, hdc, hdcBackBuf);

	tankMoveControl(ME);
	tankMoveControl(ENEMY);
	groundExplosion(hWnd);

}
Tank * MARTRISS::tankOfThisTurn(bool reverse)
{
	if (reverse)
	{
		if (Turn)
			return ENEMY;
		else
			return ME;
	}
	else
	{
		if (Turn)
			return ME;
		else
			return ENEMY;
	}
}
bool MARTRISS::checkRight(Tank* a, int Rp)
{
	for (int x = (a->myPos_x - 1) / 18; x < 64; x++)
	{
		if ( (MAP->MapBlock[ (a->myPos_y - 1) / 18 ][x]) )
		{
			if (18 * x + 1 <= Rp)
			{
				if (MAP->MapBlock[(a->myPos_y - 1) / 18 - 1][x] == 0)
				{
					if ((tankOfThisTurn()->myPos_y - 1) % 18 == 0)
					{
						tankOfThisTurn()->myPos_x -= 1;
						return false;
					}
					else
					{
						tankOfThisTurn()->myPos_x += 1;
						tankOfThisTurn()->myPos_y -= 18;
						return false;
					}
				}
				else
					return true;
			}
		}
	}
	return false;
}
bool MARTRISS::checkLeft(Tank* a, int Lp)
{
	for (int x = (a->myPos_x-1)/18; x > 0; x--)
	{
		if ((MAP->MapBlock[(a->myPos_y - 1) / 18][x]))
		{
			if (18 * (x + 1) >= Lp)
			{
				if (MAP->MapBlock[(a->myPos_y - 1) / 18 - 1][x] == 0)
				{
					if ((tankOfThisTurn()->myPos_y - 1) % 18 == 0)
					{
						tankOfThisTurn()->myPos_x += 1;
						return false;
					}
					else
					{
						tankOfThisTurn()->myPos_x -= 1;
						tankOfThisTurn()->myPos_y -= 18;
						return false;
					}
				}
				else
					return true;
			}
		}
	}
	return false;
}
bool MARTRISS::checkDown(Tank* a, int Dp)
{
	for (int y = (a->myPos_y - 1) / 18; y < 48; y++)
	{
		if ((MAP->MapBlock[y][ (a->myPos_x - 1) / 18 ]))
		{
			if (18 * y+1 <= Dp)
				return true;
		}
	}
	return false;
}
bool MARTRISS::checkBarrelUp(Tank* a, double Degree)
{
	if (a->Team)
		if (Degree >= (75. / 180.)*pi)
			return true;
		else
			return false;
	else
		if (Degree <= (105. / 180.)*pi)
			return true;
		else
			return false;
}
bool MARTRISS::checkBarrelDown(Tank* a, double Degree)
{
	if(a->Team)
		if (Degree <= (15. / 180.)*pi)
			return true;
		else
			return false;
	else
		if (Degree >= (165./180.)*pi)
			return true;
		else
			return false;
}
bool MARTRISS::checkMissile(Tank* a, int Dp)
{
	for (int y = (a->myMissile.missilePos_y - 1) / 18; y < 48; y++)
	{
		if ((MAP->MapBlock[y][(tankOfThisTurn()->myMissile.missilePos_x - 1) / 18]))
		{
			if (18 * y + 1 <= Dp)
				return true;
		}
	}
	return false;
}