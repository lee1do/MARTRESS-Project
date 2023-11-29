#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <time.h>
#include <mmsystem.h>
#include "resource.h"
#include "Tank.h"
#include "Map.h"
#include "MARTRISS.h"
#include "Credit.h"
#include "MainMenu.h"
#include "Setting.h"
#pragma comment(lib, "winmm.lib")
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("마트리스");


int Random(int a, int b)
{
	Sleep(500);
	srand(time(NULL) * 100000);
	return rand() % (b - a) + a + 1;
}
int myPos = Random(76, 476);
int enemyPos = Random(676, 1076);
Map gameMap(1);
Tank myTank(1, 0, myPos, 45, 2000);
Tank enemyTank(0, 0, enemyPos, 45, 2000);
MARTRISS GAME(&myTank, &enemyTank, &gameMap, 1, 0);
Credit credit;
MainMenu mainmenu;
Setting set;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,	CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps;
	HDC hdc, hdcBackBuf, BackGndBmp_Hdc;											                       //Bmp_Hdc->Bmp을 Hdc로 바꾼것을 의미
	HBITMAP hdcBackBmp, BackGndBmp;																		   //Bmp->비트맵을 의미
	RECT rect;																													   //실행 화면의 크기를 담을 변수
	HINSTANCE ins = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);          //윈도우의 핸들값을 저장할 변수
	static int stage = S_MAINMENU;

	switch (iMessage) {
	case WM_CREATE:
		sndPlaySound("backgroundmusic.wav", SND_ASYNC);
		return 0;
	case WM_GETMINMAXINFO://1152 864
		MoveWindow(hWnd, 100, 100, 1152, 864, true);
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 1152;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 864;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 1152;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 864;
		return 0;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_LEFT:
			if (GAME.tankOfThisTurn()->Fuel > 0)	
				GAME.tankOfThisTurn()->push_Left();			//탱크 왼쪽으로 이동
			break;
		case VK_RIGHT:
			if (GAME.tankOfThisTurn()->Fuel > 0)	
				GAME.tankOfThisTurn()->push_Right();		//탱크 오른쪽으로 이동
			break;
		case VK_UP:
			GAME.tankOfThisTurn()->push_Up();			//포신 위로 이동
			break;
		case VK_DOWN:
			GAME.tankOfThisTurn()->push_Down();		//포신 아래로 이동
			break;
		case VK_SPACE:
			GAME.tankOfThisTurn()->push_Space();		//게이지 조절
			break;
		case 0x31:
			GAME.tankOfThisTurn()->myMissile.missileMode = 1;
			break;
		case 0x32:
			if (GAME.tankOfThisTurn()->skills_Limit[0] != 0)
				GAME.tankOfThisTurn()->myMissile.missileMode = 2;
			break;
		case 0x33:
			if (GAME.tankOfThisTurn()->skills_Limit[1] != 0)
				GAME.tankOfThisTurn()->myMissile.missileMode = 3;
			break;
		case 0x34:
			if (GAME.tankOfThisTurn()->skills_Limit[2] != 0)
				GAME.tankOfThisTurn()->myMissile.missileMode = 4;
			break;
		}
		return 0;
	case WM_KEYUP:
		switch (wParam) {
		case VK_SPACE:
			GAME.tankOfThisTurn()->Shot();				//발사
			break;
		}
		return 0;
	case WM_TIMER:
		switch (wParam) {
		case CREDIT:
			credit.decreasePosy();
			InvalidateRect(hWnd, NULL, false);
			break;
		}
		InvalidateRect(hWnd, NULL, false);
		return 0;
	case WM_LBUTTONDOWN:
		if (stage == S_MAINMENU && mainmenu.clickxy(lParam) > 0)
			stage = mainmenu.clickxy(lParam);
		else if (stage == S_SETTING)
			if (!set.setImg(lParam))
				stage = S_MAINMENU;
		if (stage == S_EXITGAME)
			PostQuitMessage(0);
		InvalidateRect(hWnd, NULL, false);
		return 0;
	case WM_MOUSEMOVE:
		if (stage == S_MAINMENU)
			mainmenu.checkxy(lParam);
		InvalidateRect(hWnd, NULL, false);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		switch (stage) {
		case S_GAMEPLAY:
			SetTimer(hWnd, 1, 10, NULL);
			//더블버퍼링-1 시작
			GetClientRect(hWnd, &rect);
			hdcBackBuf = CreateCompatibleDC(hdc);
			hdcBackBmp = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
			SelectObject(hdcBackBuf, hdcBackBmp);
			BackGndBmp_Hdc = CreateCompatibleDC(hdc);
			BackGndBmp = LoadBitmap(ins, MAKEINTRESOURCE(BACKGROUND));
			SelectObject(BackGndBmp_Hdc, BackGndBmp);
			BitBlt(hdcBackBuf, 0, 0, rect.right, rect.bottom, BackGndBmp_Hdc, 0, 0, SRCCOPY);
			//더블버퍼링-1 끝

			GAME.Run(ins, hdc, hdcBackBuf, hWnd);

			//더블버퍼링-2 시작
			BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdcBackBuf, 0, 0, SRCCOPY);
			DeleteDC(hdcBackBuf);
			DeleteObject(hdcBackBmp);
			DeleteDC(BackGndBmp_Hdc);
			DeleteObject(BackGndBmp);
			//더블버퍼링-2 끝
			break;
		case S_MAINMENU:
			mainmenu.run(hdc, g_hInst);
			break;
		case S_SETTING:
			set.run(hdc, g_hInst);
			break;
		case S_CREDIT:
			SetTimer(hWnd, CREDIT, 30, NULL);
			credit.run(hWnd, hdc, g_hInst);

			if (credit.getPosy() < -2200) {
				KillTimer(hWnd, CREDIT);
				stage = S_MAINMENU;
				InvalidateRect(hWnd, NULL, false);
				credit.setPosy(0);
			}
			break;
		}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}