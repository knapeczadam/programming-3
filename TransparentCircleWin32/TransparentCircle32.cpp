// TransparentCircle32.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "TransparentCircle32.h"
#include <Windows.h>
#pragma comment(lib, "Msimg32.lib")

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst; // current instance
TCHAR szTitle[MAX_LOADSTRING]; // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING]; // the main window class name

// Forward declarations of functions included in this code module:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

bool paintRect(HDC hdc, RECT dim, COLORREF penCol, COLORREF brushCol, unsigned int opacity) {
    HDC tempHdc = CreateCompatibleDC(hdc);
    // BLENDFUNCTION blend = {AC_SRC_OVER, 0, opacity, AC_SRC_ALPHA};
    BLENDFUNCTION blend = {AC_SRC_OVER, 0, 128, AC_SRC_ALPHA};

    HBITMAP hbitmap;
    BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(BITMAPINFO));

    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = dim.right - dim.left;
    bmi.bmiHeader.biHeight = dim.bottom - dim.top;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = (dim.right - dim.left) * (dim.bottom - dim.top) * 4;

    hbitmap = CreateDIBSection(tempHdc, &bmi, DIB_RGB_COLORS, NULL, NULL, 0x0);
    SelectObject(tempHdc, hbitmap);

    SetDCPenColor(tempHdc, penCol);
    SetDCBrushColor(tempHdc, brushCol);
    FillRect(tempHdc, &dim, CreateSolidBrush(brushCol));

    bool result = AlphaBlend(hdc, dim.left, dim.top, dim.right, dim.bottom, tempHdc, dim.left, dim.top, dim.right, dim.bottom, blend);

    DeleteObject(hbitmap);
    DeleteDC(tempHdc);

    return result;
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                       _In_opt_ HINSTANCE hPrevInstance,
                       _In_ LPTSTR lpCmdLine,
                       _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_TRANSPARENTCIRCLE32, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TRANSPARENTCIRCLE32));

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

    return (int)msg.wParam;
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

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TRANSPARENTCIRCLE32));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCE(IDC_TRANSPARENTCIRCLE32);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
            // PAINTSTRUCT ps;
            // HDC hdc = BeginPaint(hWnd, &ps);
            //
            // // Get the client area dimensions
            // RECT clientRect;
            // GetClientRect(hWnd, &clientRect);
            // int width = clientRect.right - clientRect.left;
            // int height = clientRect.bottom - clientRect.top;
            //
            // // Create a compatible DC and a compatible bitmap
            // HDC hdcMem = CreateCompatibleDC(hdc);
            // HBITMAP hBitmap = CreateCompatibleBitmap(hdc, width, height);
            // HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hBitmap);
            //
            // // Set the blend function for transparency
            // BLENDFUNCTION blendFunction;
            // blendFunction.BlendOp = AC_SRC_OVER;
            // blendFunction.BlendFlags = 0;
            // blendFunction.SourceConstantAlpha = 128; // Adjust the alpha value for transparency (0 - 255)
            // blendFunction.AlphaFormat = AC_SRC_ALPHA;
            // //
            // // // Create a solid brush with a transparent color
            // HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // Red color (adjust as needed)
            // FillRect(hdcMem, &clientRect, hBrush);
            // //
            // // // Draw a transparent ellipse
            // Ellipse(hdcMem, 50, 50, 450, 450);
            // Ellipse(hdcMem, 60, 60, 550, 550);
            // //
            // // // Draw the content of the compatible DC to the window with transparency
            // AlphaBlend(hdc, 0, 0, width, height, hdcMem, 0, 0, width, height, blendFunction);
            //
            // // bit blit the bitmap onto the window
            // BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);
            //
            // // select the bitmap back into the DC
            // SelectObject(hdcMem, hOldBitmap);
            //
            // // Cleanup
            // DeleteDC (hdcMem);
            // ReleaseDC (hWnd, hdc);
            // DeleteObject (hBitmap);
            // DeleteObject (hBrush);
            //
         PAINTSTRUCT ps;
         HDC hdc = BeginPaint(hWnd, &ps);
 
         // // Get client area
         // RECT rc;
         // GetClientRect(hWnd, &rc);
         //
         // // Create a compatible bitmap for the screen
         // HDC hdcMem = CreateCompatibleDC(hdc);
         // HBITMAP hbmMem = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);
         // HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);
         //
         // // Set the blend function for transparency.
         // BLENDFUNCTION bf;
         // bf.BlendOp = AC_SRC_OVER;
         // bf.BlendFlags = 0;
         // bf.SourceConstantAlpha = 128; // semi-transparent
         // bf.AlphaFormat = AC_SRC_ALPHA;
         //
         // // Create a solid brush with a transparent color
         // HBRUSH hBrushTransparent = CreateSolidBrush(RGB(255, 0, 0)); // Red color (opaque)
         // HBRUSH hBrushOpaque = CreateSolidBrush(RGB(0, 0, 255));      // Blue color (semi-transparent)
         //
         // // Draw a semi-transparent rectangle
         // FillRect(hdcMem, &rc, hBrushTransparent);
         //
         // // Draw an opaque rectangle
         // RECT rcOverlap = { 50, 50, 150, 150 };  // Adjust the dimensions as needed
         // FillRect(hdcMem, &rcOverlap, hBrushOpaque);
         //
         // // Draw the content of the compatible DC to the window with transparency
         // AlphaBlend(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hdcMem, 0, 0, rc.right - rc.left, rc.bottom - rc.top, bf);
         //
         // // Clean up
         // SelectObject(hdcMem, hbmOld);
         // DeleteObject(hbmMem);
         // DeleteDC(hdcMem);
         // DeleteObject(hBrushTransparent);
         // DeleteObject(hBrushOpaque);
         //
            RECT a = {0, 0, 100, 100};
            paintRect(hdc, a, RGB(255, 0, 0), RGB(0, 0, 255), 128);
            RECT b = {100, 100, 200, 200};
            paintRect(hdc, b, RGB(0, 255, 0), RGB(0, 0, 255), 128);
         EndPaint(hWnd, &ps);           // EndPaint(hWnd, &ps);
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
