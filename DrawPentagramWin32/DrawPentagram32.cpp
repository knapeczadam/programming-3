// DrawPentagram32.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "DrawPentagram32.h"

#include <vector>
#include <cmath>
#include <string>
#include <sstream>

#if defined(UNICODE) or defined(_UNICODE)
#define tstring std::wstring
#define tstringstream std::wstringstream
#define tstr std::to_wstring
#else
#define tstring std::string
#define tstringstream std::stringstream
#define tstr std::to_string
#endif

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
TCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
std::vector<POINT> points;
constexpr float gPI = 3.14159265358979323846f;
int giNumOfPentagrams = 0;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_DRAWPENTAGRAM32, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAWPENTAGRAM32));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAWPENTAGRAM32));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_DRAWPENTAGRAM32);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
        {
            POINT pt;
            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);
            points.push_back(pt);
            ++giNumOfPentagrams;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_RBUTTONDOWN:
        {
            points.clear();
            giNumOfPentagrams = 0;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
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
            HDC hdc = BeginPaint(hWnd, &ps);

            // Red, black pens
            HPEN hPenRed = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            HPEN hPenBlack = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));


            constexpr int iNumOfVertices = 5;
            constexpr LONG radius = 50;
            constexpr float angle = 2 * gPI / iNumOfVertices;
#if 1
            const float offsetAngle = gPI / 2 - angle;
#else
            const float offsetAngle = 0;
#endif
            if constexpr (iNumOfVertices < 3)
            {
                break;
            }
            for (const auto & point : points)
            {
                const POINT center = point;
                for (int i = 0; i < iNumOfVertices; ++i)
                {
                    const float angle1 = angle * static_cast<float>(i) - offsetAngle;
                    const float angle2 = angle * (static_cast<float>(i) + 2) - offsetAngle;
                    // normally, f means Flags (usually multiple bit values), but here it means float
                    const float fCenterX = static_cast<float>(center.x);
                    const float fCenterY = static_cast<float>(center.y);
                    const float fromX = fCenterX + radius * std::cos(angle1);
                    const float fromY = fCenterY + radius * std::sin(angle1);
                    const float toX = fCenterX + radius * std::cos(angle2);
                    const float toY = fCenterY+ radius * std::sin(angle2);

                    if (i % 2 == 0)
                    {
                        SelectObject(hdc, hPenRed);
                    }
                    else
                    {
                        SelectObject(hdc, hPenBlack);
                    }

                    // draw
                    MoveToEx(hdc, static_cast<int>(fromX), static_cast<int>(fromY), NULL);
                    LineTo(hdc, static_cast<int>(toX), static_cast<int>(toY));
                }
            }

            tstringstream title;
            title << _T("Pentagrams: ") << giNumOfPentagrams;
            SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)title.str().c_str());

            // Delete pens
            DeleteObject(hPenRed);
            DeleteObject(hPenBlack);
            
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

// Message handler for about box.
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
