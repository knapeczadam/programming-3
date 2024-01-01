// MyApplication.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "MyFirstApplication.h"
#include <windowsx.h>

#include <string>
#include <vector>

std::vector<POINT> g_PointsVec;

// Forward declarations of functions included in this code module
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_      HINSTANCE hInstance,
                     _In_opt_   HINSTANCE hPrevInstance,
                     _In_       LPWSTR    lpCmdLine,
                     _In_       int       nCmdShow)
{
    // (1) Custom variables
    std::wstring appName = L"MyFirstApplication";
    std::wstring title   = L"My First Application";

    // (2) Register the window class (= choose the type of window you want)
    WNDCLASSEXW wcex;

    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW; //| CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYFIRSTAPPLICATION));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    //wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MYFIRSTAPPLICATION);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = appName.c_str();
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_MYFIRSTAPPLICATION));

    RegisterClassExW(&wcex);

    // (3) Create the window, store the handle, check if all went well
    HWND hWnd = CreateWindowW(  appName.c_str(), 
                                title.c_str(),          // window title
                                WS_OVERLAPPEDWINDOW,    // window style
                                CW_USEDEFAULT,          // default x
                                CW_USEDEFAULT,          // default y
                                CW_USEDEFAULT,          // default width
                                CW_USEDEFAULT,          // default height
                                nullptr, 
                                nullptr, 
                                hInstance, 
                                nullptr);

    if (!hWnd)
    {
        MessageBox(NULL, L"Failure to create program window", L"Error", MB_ICONERROR);
        return 0;
    }

    // (4) Set the window to show
    ShowWindow(hWnd, nCmdShow);	    // set the window to show mode
    UpdateWindow(hWnd);	            // update 

    // (5) load keyboard shortcuts, start the Windows message loop
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYFIRSTAPPLICATION));
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // (6) Close with received Quit message information
    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_ACTIVATE:
        if (wParam == WA_INACTIVE)
        {
            SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM) L"This window is inactive; go away.");
        }
        else
        {
            SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM) L"Lines");
        }
        return 0;

    case WM_LBUTTONUP:
        g_PointsVec.push_back({ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) });
        InvalidateRect(hWnd, NULL, true);
        return 0;

    case WM_RBUTTONUP:
        g_PointsVec.clear();
        InvalidateRect(hWnd, NULL, true);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            HPEN blackPen = CreatePen(PS_SOLID, 1, RGB(80, 80, 50));
            HPEN oldPen = (HPEN)SelectObject(hdc, blackPen);

            HBRUSH blackBrush = CreateSolidBrush(RGB(80, 80, 50));
            HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, blackBrush);

            if (g_PointsVec.size() > 0)
            {
                MoveToEx(hdc, g_PointsVec[0].x, g_PointsVec[0].y, 0);
                Ellipse(hdc, g_PointsVec[0].x - 2, g_PointsVec[0].y - 2, g_PointsVec[0].x + 2, g_PointsVec[0].y + 2);

                for (int count = 1; count < (int)g_PointsVec.size(); ++count)
                {
                    LineTo(hdc, g_PointsVec[count].x, g_PointsVec[count].y);
                    Ellipse(hdc, g_PointsVec[count].x - 2, g_PointsVec[count].y - 2, g_PointsVec[count].x + 2, g_PointsVec[count].y + 2);
                }
            }

            SelectObject(hdc, oldBrush);
            DeleteObject(blackBrush);

            SelectObject(hdc, oldPen);
            DeleteObject(blackPen);

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
