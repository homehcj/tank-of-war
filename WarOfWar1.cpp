// WarOfWar1.cpp : 定义应用程序的入口点。
//

#include "pch.h"
#include "framework.h"
#include "WarOfWar1.h"
#include"CTank.h"
#include"CWall.h"
#include"Cfire.h"
#include"Cboss.h"
#include<atlstr.h>
#include<cstring>
#include"Crecordpoint.h"


#define MAX_LOADSTRING 100
int timeflg;//控制时间减分
int flgchar = 0;//检测是否按键
int flg=0;
Cboss boss;
Cfire fire;
CTank mytank(500,250,1);
int munpoint = 0;
int pass= 1;
Crecordpoint record;
// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    WayProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。
    MessageBox(NULL, _T("点击确定加载关卡，加载需要时间请等待"), _T("Tip"), MB_OK);
    boss.print(11, 1);
    MessageBox(NULL, _T("请将窗口最大化，否则将不能看到游戏全部内容"), _T("重要提醒"), MB_OK);
   
    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WAROFWAR1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WAROFWAR1));

    MSG msg;
    
    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WAROFWAR1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WAROFWAR1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW|WS_MAXIMIZE,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
  /* HWND hWay = CreateDialog(hInstance, (LPCTSTR)IDD_WAYBOX, hWnd, WayProc);*/

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    SetTimer(hWnd, 1, 10, NULL);
    HDC hdc;
    switch (message)
    {
    case WM_TIMER:
    {
        if ((timeflg >= 200)&&(flgchar!=0))//减分速度&&检测游戏是否开始
        {
            munpoint--;//随时间减分
            timeflg = 0;
        }
        timeflg++;
        InvalidateRect(hWnd, NULL, true);
        UpdateWindow(hWnd);
        hdc = GetDC(hWnd);//当不在WM_print画图时用GetDC
        
        ////绘制边界
        //HBRUSH bursh = CreateSolidBrush(RGB(125, 125, 125));
        //HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, bursh);
        //Rectangle(hdc, 40, 20, 1500, 700);
        //SelectObject(hdc, oldbrush);
        //DeleteObject(bursh);
                          
        //绘制炮弹
        fire.drawfire(hdc);
        //绘制boss
         boss.draw(hdc);
         if (boss.mun == 0)
         {
            boss.print(11, 1);//打完重置；
            //过关奖励；
            mytank.hp++;
            munpoint = munpoint+5;
            pass++;//关卡
         }
            
        // 绘制坦克
        if ((!mytank.printtank(hdc))&&(flg==0))
        {
            record.record(munpoint, pass);
            flg++;
            if (MessageBox(NULL, _T("Game Over"), _T("Tip"), MB_OK) == 1)
            {
                PostQuitMessage(0);
            }
        }
        ReleaseDC(hWnd, hdc);
        
        

        //检测
        //左右墙
        if ((mytank.x<40)||((mytank.x+70)>1500))
        {
            mytank.hp--;
            //初始化坦克位置
            mytank.x = 500;
            mytank.y = 250;
            munpoint = munpoint - 1;
        }
        //上下墙
        if ((mytank.y < 20) || ((mytank.y + 40) > 400))
        {
            mytank.hp--;
            //初始化坦克位置
            mytank.x = 500;
            mytank.y = 250;
            munpoint = munpoint - 1;
        }
        
        //炮弹和坦克
       
         //坦克左上边界
            for (int i = 0; i < fire.mun; i++)
            {
                if (fire.boollive[i] != 0)
                {
                    if ((mytank.x < fire.x[i]) && (mytank.y < fire.y[i]))
                    {
                        //坦克左下边界
                        if ((mytank.x < fire.x[i]) && ((mytank.y + 40) > fire.y[i]))
                        {
                            //坦克右上边界
                            if (((mytank.x + 70) > fire.x[i]) && (mytank.y < fire.y[i]))
                            {
                                //坦克右下边界
                                if (((mytank.x + 70) > fire.x[i]) && ((mytank.y + 40) > fire.y[i]))
                                {
                                    mytank.hp--;
                                    //初始化坦克位置
                                    mytank.x = 500;
                                    mytank.y = 250;
                                    munpoint = munpoint - 1;
                                }
                            }
                        }
                    }
                }

            }
           
        //炮弹击中boss判定
            for (int i = 1; i < 8; i++)
            {
                for (int j = 1; j < 4; j++)
                {
                    if (boss.piont[i][j] == 1)
                    {
                        for (int k = 0; k < fire.mun; k++)
                        {
                            //判断炮弹是否存在
                            if (fire.boollive[k]!=0)
                            {
                                //boss左上边界
                                if (((i*200) < fire.x[k]) && ((j*100) < fire.y[k]))
                                {
                                    //boss左下边界
                                    if (((i*200) < fire.x[k]) && (((j*100) + 40) > fire.y[k]))
                                    {
                                        //boss右上边界
                                        if ((((i*200) + 40) > fire.x[k]) && ((j*100) < fire.y[k]))
                                        {
                                            //boss右下边界
                                            if ((((i * 200) + 40) > fire.x[k]) && (((j * 100) + 40) > fire.y[k]))
                                            {
                                                boss.piont[i][j] = 0;
                                                fire.boollive[k] = 0;//炮弹和boss消失
                                                boss.mun--;
                                                munpoint++;//分数增加
                                            }
                                        }
                                    }
                                }
                            }

                        }

                    }
                }
            }
            //坦克和boss
            for (int i = 1; i < 8; i++)
            {
                for (int j = 1; j < 4; j++)
                {
                    if (boss.piont[i][j] == 1)
                    {
                        //左上端点-------------------------------------------------
                        //坦克左上边界
                        if ((mytank.x < (i*200)) && (mytank.y < (j*100)))
                        {
                            //坦克左下边界
                            if ((mytank.x < (i*200)) && ((mytank.y + 40) > (j * 100)))
                            {
                                //坦克右上边界
                                if (((mytank.x + 70) > (i * 200)) && (mytank.y < (j * 100)))
                                {
                                    //坦克右下边界
                                    if (((mytank.x + 70) > (i * 200)) && ((mytank.y + 40) > (j * 100)))
                                    {
                                        mytank.hp--;
                                        //初始化坦克位置
                                        mytank.x = 500;
                                        mytank.y = 250;
                                        munpoint = munpoint - 2;
                                    }
                                        
                                }
                            }
                        }

                        //左下端点-------------------------------------------------
                        //坦克左上边界
                        if ((mytank.x < (i * 200)) && (mytank.y < (j * 100+40)))
                        {
                            //坦克左下边界
                            if ((mytank.x < (i * 200)) && ((mytank.y + 40) > (j * 100+40)))
                            {
                                //坦克右上边界
                                if (((mytank.x + 70) > (i * 200)) && (mytank.y < (j * 100+40)))
                                {
                                    //坦克右下边界
                                    if (((mytank.x + 70) > (i * 200)) && ((mytank.y + 40) > (j * 100 + 40)))
                                    {
                                        mytank.hp--;
                                        //初始化坦克位置
                                        mytank.x = 500;
                                        mytank.y = 250;
                                        munpoint = munpoint - 2;
                                    }
                                }
                            }
                        }

                        //右下端点-------------------------------------------------
                        //坦克左上边界
                        if ((mytank.x < (i * 200+40)) && (mytank.y < (j * 100 + 40)))
                        {
                            //坦克左下边界
                            if ((mytank.x < (i * 200+40)) && ((mytank.y + 40) > (j * 100 + 40)))
                            {
                                //坦克右上边界
                                if (((mytank.x + 70) > (i * 200+40)) && (mytank.y < (j * 100 + 40)))
                                {
                                    //坦克右下边界
                                    if (((mytank.x + 70) > (i * 200 + 40)) && ((mytank.y + 40) > (j * 100 + 40)))
                                    {
                                        mytank.hp--;
                                        //初始化坦克位置
                                        mytank.x = 500;
                                        mytank.y = 250;
                                        munpoint = munpoint - 2;
                                    }

                                }
                            }
                        }

                        //右上端点-------------------------------------------------
                        //坦克左上边界
                        if ((mytank.x < (i * 200 + 40)) && (mytank.y < (j * 100 )))
                        {
                            //坦克左下边界
                            if ((mytank.x < (i * 200 + 40)) && ((mytank.y + 40) > (j * 100 )))
                            {
                                //坦克右上边界
                                if (((mytank.x + 70) > (i * 200 + 40)) && (mytank.y < (j * 100 )))
                                {
                                    //坦克右下边界
                                    if (((mytank.x + 70) > (i * 200 + 40)) && ((mytank.y + 40) > (j * 100)))
                                    {
                                        mytank.hp--;
                                        //初始化坦克位置
                                        mytank.x = 500;
                                        mytank.y = 250;
                                        munpoint = munpoint - 2;
                                    }

                                }
                            }
                        }
                    }
                }
            }
    }
    break;
    case WM_CHAR:
    {   
        
        //hdc = GetDC(hWnd);//当不在WM_print画图时用GetDC
        //重绘当前窗口
        /*InvalidateRect(hWnd,NULL, true);
        UpdateWindow(hWnd);*/
        //下移
        if (wParam == 115)
        {
            mytank.y= mytank.y + 15;
            flgchar = 1;
        }
        //上移
        if (wParam == 119)
        {
            mytank.y = mytank.y - 15;
            flgchar = 1;
        }
        //左移
        if (wParam == 97)
        {
            mytank.x= mytank.x - 15;
            flgchar = 1;
        }
        //右移
        if (wParam == 100)
        {
            mytank.x = mytank.x + 15;
            flgchar = 1;
        }
        //空格32开炮
        if (wParam == 32)
        {
            fire.fireset(mytank.x+70, mytank.y+18);
            flgchar = 1;
        }
        ////绘制障碍物
        //block.print(hdc);
        //
        //
        //if (!mytank.printtank(hdc))
        //{
        //    MessageBox(NULL, _T("Game Over"), _T("Tip"), MB_OK);
        //}
        //ReleaseDC(hWnd,hdc);
    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_WAY:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_WAYBOX), hWnd, WayProc);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {

        PAINTSTRUCT ps;  
        hdc = BeginPaint(hWnd, &ps);

        //输出相关属性
        CString str;
        str.Format(_T("分数：%d"),munpoint);
        TextOut(hdc, 500, 500, str, str.GetLength());
        str.Format(_T("关卡：%d"), pass);
        TextOut(hdc, 500, 550, str, str.GetLength());
        str.Format(_T("坦克生命：%d"), mytank.hp);
        TextOut(hdc, 500, 600, str, str.GetLength());

        // TODO: 在此处添加使用 hdc 的任何绘图代码...
        //绘制边界
        
        Rectangle(hdc, 40, 20, 1500, 400);
        


        EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

//游戏方法对话框
INT_PTR CALLBACK    WayProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

