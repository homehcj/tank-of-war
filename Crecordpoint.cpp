#include "pch.h"
#include "Crecordpoint.h"
#include<iostream>
#include<fstream>
#include<time.h>
using namespace std;
bool Crecordpoint::record(int point,int pass)
{
    time_t now = time(0);
    // �� now ת��Ϊ�ַ�����ʽ
    char a[50];
     ctime_s(a,49,&now);
    //�������
    ofstream fs("point.html",ios::app);
        fs << "<tittle>" << endl;
        fs << "<b>" << "ʱ��:"<<"\t"<<a<< "</b>" << endl;
        fs << "</tittle>" << endl;
        fs << "<p>" << endl;
        fs << "<b>" << "�÷�:" << "</b>" << point << "\t\t" << "<b>" <<"ͨ��"<<pass-1<<"��"<< "</b>" << endl;
        fs << "</p>" << endl;
    fs.close();

    return false;
}
