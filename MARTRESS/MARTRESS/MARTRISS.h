#include <windows.h>
#include "Tank.h"
#include "Map.h"
#ifndef MARTRISS_H
#define MARTRISS_H
class MARTRISS
{
private:
	bool Turn;
	Tank *ME;
	Tank *ENEMY;
	Map *MAP;
public:
	MARTRISS(Tank *ME, Tank *ENEMY, Map *MAP, bool Turn, bool useAI) {this->ME = ME; this->ENEMY = ENEMY; this->MAP = MAP; this->Turn = Turn;}
	Tank * tankOfThisTurn(bool reverse=false);//이번턴의 탱크가 누구인지 반환
	void Run(HINSTANCE ins, HDC hdc, HDC hdcBackBuf, HWND hWnd);//두 탱크의 Run함수 돌림
	void tankMoveControl(Tank* a);
	void groundExplosion(HWND hWnd);
	bool checkRight(Tank* a, int Rp);
	bool checkLeft(Tank* a, int Lp);
	bool checkDown(Tank* a, int Dp);
	bool checkBarrelUp(Tank* a, double Degree);
	bool checkBarrelDown(Tank* a, double Degree);
	bool checkMissile(Tank* a, int Dp);
};
#endif
