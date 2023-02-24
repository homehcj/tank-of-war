#include "pch.h"
#include "Cboss.h"
#include<time.h>

bool Cboss::print(int max, int min)
{	
	int z, l;
	mun =random(max, min);
	for (int i = 0; i <mun; i++)
	{
		while (true)
		{
			z = random(7, 1);
			l = random(3, 1);
			if (piont[z][l] != 1)
			{
				piont[z][l] = 1;
				break;
			}
		}
	}
    return false;
}

int Cboss::draw(HDC hdc)
{
	HBRUSH bursh = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, bursh);
	for (int i = 1; i < 8; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			if (piont[i][j] == 1)
			{
				Rectangle(hdc, (i*200),( j*100),( i*200 + 40),( j*100 + 40));
				
			}
		}
	}
	SelectObject(hdc, oldbrush);
	DeleteObject(bursh);
	
	return 0;
}

inline int Cboss::random(int max, int min)
{
	int a;
		srand(time(NULL));
		a = (rand() % (max - min + 1)) + min;

	return a;
}
