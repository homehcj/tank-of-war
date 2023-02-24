#include "pch.h"
#include "Cfire.h"
#include<time.h>

bool Cfire::fireset(int x,int y)
{
   this-> x[mun] = x;
   this-> y[mun] = y;
   boollive[mun] = 1;
    mun++;
    if (mun==4999)
    {
        mun = 0;
    }
    return false;
}

bool Cfire::drawfire(HDC hdc)
{
    for (int i = 0; i < mun; i++)
    {
        if (boollive[i]==1)
        {
        Rectangle(hdc, x[i], y[i], x[i] + 4, y[i] + 4);
        }
    }
    firemove();
    return false;
}

bool Cfire::firemove()
{
    for (int i = 0; i < mun; i++)
    {
        if (x[i] >= 1500)
        {
            x[i] = 40;//子弹碰到边界返回
            y[i] = random(400,20,y[i]);//子弹y位置随机出现
        }
        x[i]=x[i]+4;//炮弹速度；4合适
    }
    return false;
}

inline int Cfire::random(int max, int min,int b)
{
    int a;
    //两次随机
    srand(flg+time(NULL)%100);
    srand(rand()+b);

    a = (rand() % (max - min + 1)) + min;
    flg++;
    return a;
}
