#include "pch.h"
#include "CTank.h"

bool CTank::printtank(HDC hdc)
{
	HBRUSH bursh = CreateSolidBrush(RGB(0, 255, 100));
	HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, bursh);
	if (hp > 0)
	{
	//����̹�˳���
	Rectangle(hdc,x,y,x+70,y+40);
	SelectObject(hdc, oldbrush);
	DeleteObject(bursh);
	//����̹����̨
	Ellipse(hdc, x + 10, y + 10, x + 40, y + 30);
	//�����ڹ�
	Rectangle(hdc, x + 40, y + 18, x + 65, y + 22);
	return true;
	}
	else
	{
		return false;
	}
	
}

CTank::CTank(int x,int y,int hp)
{
	this->x = x;
	this->y = y;
	this->hp = hp;
}

