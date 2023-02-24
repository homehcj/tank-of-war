#pragma once

class Cboss
{
public:
	int piont[8][4];
	bool hit[40];
	int mun;//出现个数
	int live;
	bool print(int max,int min);
	int draw(HDC hdc);
	inline int random(int max, int min);
};

