// MyApplication.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "MyFirstApplication.h"

#include <string>

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
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYFIRSTAPPLICATION));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MYFIRSTAPPLICATION);
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
