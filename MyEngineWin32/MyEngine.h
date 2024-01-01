#pragma once
#include "framework.h"

class MyEngine final
{
public:
    MyEngine(HINSTANCE hInstance, int nCmdShow, const tstring& title, int width, int height, bool fullscreen);
    ~MyEngine();

    int Run();

private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
    ATOM MyRegisterClass();
    BOOL InitInstance(int nCmdShow);

public:
private:
    int m_Width;
    int m_Height;
    tstring m_ClassName;

    const int m_MaxLoadString = 100;
};
