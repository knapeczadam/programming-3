// SaveBitmapToFile32.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "SaveBitmapToFile32.h"

#include <string>
#include <sstream>
#include <iostream>

#define MAX_LOADSTRING 100

#if defined(UNICODE) or defined(_UNICODE)
#define tstring std::wstring
#define tcout std::wcout
#define tcin std::wcin
#define tstringstream std::wstringstream
#else
#define tstring std::string
#define tcout std::cout
#define tcin std::cin
#define tstringstream std::stringstream
#endif

void SaveBitmapToFile32(HBITMAP bitmap, tstring fileName, int width, int height, HDC hDC)
{
    BYTE* data = new BYTE[width * height * 4];

    BITMAPINFO Bmi;
    memset (&Bmi, 0, sizeof(BITMAPINFO));
    Bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    Bmi.bmiHeader.biWidth = width;
    Bmi.bmiHeader.biHeight = height;
    Bmi.bmiHeader.biPlanes = 1;
    Bmi.bmiHeader.biBitCount = 32;
    Bmi.bmiHeader.biCompression = BI_RGB;
    Bmi.bmiHeader.biSizeImage = width * height * 4;

    GetDIBits (hDC, bitmap, 0, height, data, (BITMAPINFO*) &Bmi, DIB_RGB_COLORS);

    int sz = Bmi.bmiHeader.biSizeImage;

    BITMAPFILEHEADER bfh;
    bfh.bfType = ('M' << 8) + 'B';
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    bfh.bfSize = sz + bfh.bfOffBits;
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;

    HANDLE hFile = ::CreateFile(fileName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_WRITE,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hFile == INVALID_HANDLE_VALUE) return;

    DWORD dw;
    WriteFile( hFile, &bfh, sizeof(bfh), &dw, NULL);
    WriteFile( hFile, &Bmi.bmiHeader, sizeof(BITMAPINFOHEADER), &dw, NULL);
    WriteFile( hFile, data, sz, &dw, NULL);
    CloseHandle(hFile);

    delete[] data;
    CloseHandle(hFile);
}

void SaveBitmapToFile24(HBITMAP hBitmap, tstring lpszFileName, int width, int height, HDC hDC)
{
    // Create a BITMAPINFO structure
    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;  // Negative height to ensure a top-down DIB
    bi.biPlanes = 1;
    bi.biBitCount = 24;  // 24 bits per pixel for RGB
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;  // Size can be 0 for BI_RGB bitmaps
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    // Create a file and device-independent bitmap (DIB) section
    HANDLE hFile = CreateFile(lpszFileName.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == NULL)
    {
        MessageBox(NULL, _T("Error creating file"), _T("Error"), MB_OK | MB_ICONERROR);
        return;
    }

    // Write the BITMAPFILEHEADER to the file
    BITMAPFILEHEADER bmfHeader;
    bmfHeader.bfType = 0x4D42;  // "BM"
    bmfHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + width * height * 3;  // 3 bytes per pixel for RGB
    bmfHeader.bfReserved1 = 0;
    bmfHeader.bfReserved2 = 0;
    bmfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    DWORD dwBytesWritten;
    WriteFile(hFile, &bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);

    // Write the BITMAPINFOHEADER to the file
    WriteFile(hFile, &bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);

    // Get the bitmap data
    BYTE* pData = new BYTE[width * height * 3];  // 3 bytes per pixel for RGB
    GetDIBits(hDC, hBitmap, 0, height, pData, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    // Write the bitmap data to the file
    WriteFile(hFile, pData, width * height * 3, &dwBytesWritten, NULL);

    // Clean up
    delete[] pData;
    CloseHandle(hFile);
}

// Global Variables:
HINSTANCE hInst;                                // current instance
TCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

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
    LoadString(hInstance, IDC_SAVEBITMAPTOFILE32, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SAVEBITMAPTOFILE32));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SAVEBITMAPTOFILE32));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(RGB(255, 0, 255));
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_SAVEBITMAPTOFILE32);
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
        // when mouse button is pressed
    case WM_LBUTTONDOWN:
        {
            // get the device context of the screen
            HDC hdcWindow = GetDC(hWnd);

            // get the size of the client area
            RECT rcClient;
            GetClientRect(hWnd, &rcClient);
            int width = rcClient.right - rcClient.left;
            int height = rcClient.bottom - rcClient.top;

            // create a compatible DC
            HDC hDCMem = CreateCompatibleDC(hdcWindow);

            // create a compatible bitmap and select it into the compatible DC
            HBITMAP hBitmap = CreateCompatibleBitmap(hdcWindow, width, height);
            HBITMAP hBmpOld = (HBITMAP)SelectObject(hDCMem, hBitmap);

            // copy the client area to the compatible DC
            BitBlt(hDCMem, 0, 0, width, height, hdcWindow, 0, 0, SRCCOPY);

            // save the bitmap to a file
            // tstring fileName = _T("C:\\Users\\Public\\Documents\\test.bmp");
            tstring fileName = _T("clientarea.bmp");
            SaveBitmapToFile24(hBitmap, fileName.c_str(), width, height, hDCMem);

            // clean up
            SelectObject(hDCMem, hBmpOld);
            DeleteDC(hDCMem);
            ReleaseDC(hWnd, hdcWindow);
            
            // Note: Do not delete hBitmap here, as it is still in use by the file-saving function
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
            // TODO: Add any drawing code that uses hdc here...
            TextOut (hdc, 10, 10, _T("Hello, world!"), 13);
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
