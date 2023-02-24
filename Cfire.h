#pragma once
class Cfire
{
public:
	int x[5000] = {-100};
	int y[5000] = {-100};
	bool boollive[5000] = { 0 };

	int flg;//随机变量种子
	int mun=0;
	bool fireset(int x, int y);
	bool drawfire(HDC hdc);
private:
	bool firemove();
	inline int random(int max, int min,int b=0);
};

