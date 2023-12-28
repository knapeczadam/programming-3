// ExamPrepQuestion232.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "ExamPrepQuestion232.h"

#define _USE_MATH_DEFINES

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
    LoadString(hInstance, IDC_EXAMPREPQUESTION232, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EXAMPREPQUESTION232));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EXAMPREPQUESTION232));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_EXAMPREPQUESTION232);
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
    case WM_ACTIVATE:
        {
            if (LOWORD(wParam) == WA_INACTIVE)
            {
                SetWindowText(hWnd, _T("This window is inactive; go away."));
            }
            else
            {
                SetWindowText(hWnd, _T("Heptragrams"));
            }
        }
        break;
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
            constexpr int lineWidth = 2;
            HPEN hRedPen = CreatePen(PS_SOLID, lineWidth, RGB(255, 0, 0));
            HPEN hBlackPen = CreatePen(PS_SOLID, lineWidth, RGB(0, 0, 0));

            // Red, black brushes
            HBRUSH hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
            HBRUSH hBlackBrush = CreateSolidBrush(RGB(0, 0, 0));

            // Select red brush
            // HBRUSH hOldBrush = static_cast<HBRUSH>(SelectObject(hdc, hRedBrush));
            HBRUSH hOldBrush = static_cast<HBRUSH>(SelectObject(hdc, GetStockObject(NULL_BRUSH)));
            // select red pen
            HPEN hOldPen = static_cast<HPEN>(SelectObject(hdc, hBlackPen));

            // set the brush to be transparent
            SetBkMode(hdc, TRANSPARENT);

            constexpr int iNumOfVertices = 9;
            constexpr LONG radius = 50;
            constexpr float angle = 2 * gPI / iNumOfVertices;

            static_assert(iNumOfVertices % 2 == 1, "iNumOfVertices must be odd");

            const float offsetAngle = gPI / 2 - angle - gPI;

            if constexpr (iNumOfVertices < 3)
            {
                break;
            }
            for (int idx = 0; idx < points.size(); ++idx)
            {
                POINT pt = points[idx];
                const POINT center = pt;
                Ellipse(hdc, pt.x - radius, pt.y - radius, pt.x + radius, pt.y + radius);
                for (int i = 0; i < iNumOfVertices; ++i)
                {
                    const float angle1 = angle * static_cast<float>(i) + offsetAngle;
                    const float angle2 = angle * static_cast<float>(i + 2) + offsetAngle;
                    const float fCenterX = static_cast<float>(center.x);
                    const float fCenterY = static_cast<float>(center.y);
                    const float fromX = fCenterX + radius * std::cos(angle1);
                    const float fromY = fCenterY - radius * std::sin(angle1);
                    const float toX = fCenterX + radius * std::cos(angle2);
                    const float toY = fCenterY - radius * std::sin(angle2);

                    MoveToEx(hdc, static_cast<int>(fromX), static_cast<int>(fromY), NULL);
                    LineTo(hdc, static_cast<int>(toX), static_cast<int>(toY));
                    
                }
                
                // Draw the number of pentagrams
                tstringstream ss;
                // ss << pt.x << _T(", ") << pt.y;
                ss << idx + 1;
                tstring str = ss.str();
                TextOut(hdc, pt.x - radius, pt.y - radius, str.c_str(), str.length());

            }

            tstringstream title;
            title << _T("Heptragrams: ") << giNumOfPentagrams;
            SetWindowText(hWnd, title.str().c_str());
            // SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)title.str().c_str());

            // Select the old brush into the device context
            SelectObject(hdc, hOldBrush);

            // Select the old pen into the device context
            SelectObject(hdc, hOldPen);

            // Cleanup
            DeleteObject(hRedBrush);
            DeleteObject(hBlackBrush);
            DeleteObject(hRedPen);
            DeleteObject(hBlackPen);
            
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
