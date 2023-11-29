#include <iostream>
#include <windows.h>
#include "resource.h"
#include "Map.h"
Map::Map(int mapNum)
{
	this->mapNum = mapNum;
}
void Map::Run(HINSTANCE ins, HDC hdc, HDC hdcBackBuf)
{
	Draw(ins,hdc,hdcBackBuf);
}
void Map::Draw(HINSTANCE ins, HDC hdc, HDC hdcBackBuf)
{
	HDC DirtBmp_hdc, GlassBmp_hdc, PanelBmp_hdc;
	HBITMAP DirtBmp, GlassBmp,PanelBmp;
	DirtBmp_hdc = CreateCompatibleDC(hdc);
	GlassBmp_hdc= CreateCompatibleDC(hdc);
	PanelBmp_hdc = CreateCompatibleDC(hdc);
	DirtBmp = LoadBitmap(ins, MAKEINTRESOURCE(DIRT));
	GlassBmp= LoadBitmap(ins, MAKEINTRESOURCE(GRASS));
	PanelBmp = LoadBitmap(ins, MAKEINTRESOURCE(PANEL));
	SelectObject(DirtBmp_hdc, DirtBmp);
	SelectObject(GlassBmp_hdc, GlassBmp);
	SelectObject(PanelBmp_hdc, PanelBmp);
	for (int i = 0; i < 48; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			if (MapBlock[i][j] == 2)
				BitBlt(hdcBackBuf, j * 18, i * 18, 18, 18, GlassBmp_hdc, 0, 0, SRCCOPY);
			else if (MapBlock[i][j])
				BitBlt(hdcBackBuf, j*18, i*18, 18, 18, DirtBmp_hdc, 0, 0, SRCCOPY);
		}
	}
	BitBlt(hdcBackBuf, 0, 666, 1152, 160, PanelBmp_hdc, 0, 0, SRCCOPY);
	BitBlt(hdcBackBuf, 0, 0, 1152, 160, PanelBmp_hdc, 0, 0, SRCCOPY);
	DeleteDC(PanelBmp_hdc);
	DeleteObject(PanelBmp);
	DeleteDC(GlassBmp_hdc);
	DeleteObject(GlassBmp);
	DeleteDC(DirtBmp_hdc);
	DeleteObject(DirtBmp);
}