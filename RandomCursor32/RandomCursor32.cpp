// RandomCursor32.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "RandomCursor32.h"

#include <random>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
TCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int GetThreadSafeRandomNumber(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}

TIMERPROC TriggetSetCursorEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    SetCursor(LoadCursor(NULL, IDC_ARROW));
    return 0;
}

HCURSOR g_hCursor;
void RandomizeCursor()
{
    int cursorID;
    cursorID = GetThreadSafeRandomNumber(0, 16);
    switch (cursorID)
    {
    case 0:
        g_hCursor = LoadCursor(NULL, IDC_ARROW);
        break;
    case 1:
        g_hCursor = LoadCursor(NULL, IDC_IBEAM);
        break;
    case 2:
        g_hCursor = LoadCursor(NULL, IDC_WAIT);
        break;
    case 3:
        g_hCursor = LoadCursor(NULL, IDC_CROSS);
        break;
    case 4:
        g_hCursor = LoadCursor(NULL, IDC_UPARROW);
        break;
    case 5:
        g_hCursor = LoadCursor(NULL, MAKEINTRESOURCE(32631));
        break;
    case 6:
        g_hCursor = LoadCursor(NULL, IDC_SIZENWSE);
        break;
    case 7:
        g_hCursor = LoadCursor(NULL, IDC_SIZENESW);
        break;
    case 8:
        g_hCursor = LoadCursor(NULL, IDC_SIZEWE);
        break;
    case 9:
        g_hCursor = LoadCursor(NULL, IDC_SIZENS);
        break;
    case 10:
        g_hCursor = LoadCursor(NULL, IDC_SIZEALL);
        break;
    case 11:
        g_hCursor = LoadCursor(NULL, IDC_NO);
        break;
    case 12:
        g_hCursor = LoadCursor(NULL, IDC_HAND);
        break;
    case 13:
        g_hCursor = LoadCursor(NULL, IDC_APPSTARTING);
        break;
    case 14:
        g_hCursor = LoadCursor(NULL, IDC_HELP);
        break;
    case 15:
        g_hCursor = LoadCursor(NULL, IDC_PIN);
        break;
    case 16:
        g_hCursor = LoadCursor(NULL, IDC_PERSON);
        break;
    default:
        g_hCursor = LoadCursor(NULL, IDC_ARROW);
        break;
    }
}

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
    LoadString(hInstance, IDC_RANDOMCURSOR32, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RANDOMCURSOR32));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RANDOMCURSOR32));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_RANDOMCURSOR32);
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

    // SetTimer(hWnd, 1, 1000, (TIMERPROC)TriggetSetCursorEvent);
    SetTimer(hWnd, 1, 1000, NULL);
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
    case WM_TIMER:
        {
            if (wParam == 1)
            {
                RandomizeCursor();
                // SetCursor(NULL); // I'm not quite sure we need this
                SetCursor(g_hCursor);
            }
        }
        break;
    case WM_SETCURSOR:
        {
            if (LOWORD(lParam) == HTCLIENT)
            {
                SetCursor(g_hCursor);
                return TRUE;
            }
            return FALSE;
        }
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
            // TODO: Add any drawing code that uses hdc here...
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
