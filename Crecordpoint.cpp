#include "pch.h"
#include "Crecordpoint.h"
#include<iostream>
#include<fstream>
#include<time.h>
using namespace std;
bool Crecordpoint::record(int point,int pass)
{
    time_t now = time(0);
    // 把 now 转换为字符串形式
    char a[50];
     ctime_s(a,49,&now);
    //保存分数
    ofstream fs("point.html",ios::app);
        fs << "<tittle>" << endl;
        fs << "<b>" << "时间:"<<"\t"<<a<< "</b>" << endl;
        fs << "</tittle>" << endl;
        fs << "<p>" << endl;
        fs << "<b>" << "得分:" << "</b>" << point << "\t\t" << "<b>" <<"通过"<<pass-1<<"关"<< "</b>" << endl;
        fs << "</p>" << endl;
    fs.close();

    return false;
}
