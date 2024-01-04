// MyApplication.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "MyEngine.h"
#include <windowsx.h>

#include "MyApplication.h"

// initialize statics
HINSTANCE MyEngine::m_Instance{};
int MyEngine::m_Show{};
MyEngine* MyEngine::m_MyEnginePtr{};

// WinMain
int APIENTRY wWinMain(_In_      HINSTANCE hInstance,
            _In_opt_   HINSTANCE hPrevInstance,
            _In_       LPWSTR    lpCmdLine,
            _In_       int       nCmdShow)
{
    MyEngine::Initialize(hInstance, nCmdShow);

    int result = MyEngine::GetSingleton()->Run(new MyApplication());

    delete MyEngine::GetSingleton();

    return result;
}

// WndProc function
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return MyEngine::GetSingleton()->HandleEvent(hWnd, message, wParam, lParam);
}

void MyEngine::Initialize(HINSTANCE hInstance, int nCmdShow)
{
    m_Instance = hInstance;
    m_Show = nCmdShow;
}

MyEngine* MyEngine::GetSingleton()
{
    if (m_MyEnginePtr == nullptr) m_MyEnginePtr = new MyEngine();
    
    return m_MyEnginePtr;
}

// constructor
MyEngine::MyEngine()
{
    // (1) Custom variables
    m_AppName = L"MyApplication";
    m_Title = L"My Application";

    // (2) Register the window class (= choose the type of window you want)
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_Instance;
    wcex.hIcon = LoadIcon(m_Instance, MAKEINTRESOURCE(IDI_MYAPPLICATION));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    //wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MYFIRSTAPPLICATION);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = m_AppName.c_str();
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_MYAPPLICATION));

    RegisterClassExW(&wcex); 
}

MyEngine::~MyEngine()
{
    // nothing to destroy
}

int MyEngine::Run(MyApplication* applicationPtr)
{
    m_MyApplicationPtr = applicationPtr;

    // (3) Create the window, store the handle, check if all went well
    HWND hWnd = CreateWindowW(  m_AppName.c_str(),
                                m_Title.c_str(),        // window title
                                WS_OVERLAPPEDWINDOW,    // window style
                                CW_USEDEFAULT,          // default x
                                CW_USEDEFAULT,          // default y
                                CW_USEDEFAULT,          // default width
                                CW_USEDEFAULT,          // default height
                                nullptr,
                                nullptr,
                                m_Instance,
                                nullptr);

    if (!hWnd)
    {
        MessageBox(NULL, L"Failure to create program window", L"Error", MB_ICONERROR);

        // this would be a nice place for a throw
    }

    // (4) Set the window to show
    ShowWindow(hWnd, m_Show);	    // set the window to show mode
    UpdateWindow(hWnd);	            // update

    // (5) load keyboard shortcuts, start the Windows message loop
    HACCEL hAccelTable = LoadAccelerators(m_Instance, MAKEINTRESOURCE(IDC_MYAPPLICATION));
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
    return (int)msg.wParam;
}

LRESULT MyEngine::HandleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    m_hWnd = hWnd;

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
        if (wParam == WA_INACTIVE) m_MyApplicationPtr->Activate(false);
        else m_MyApplicationPtr->Activate(true);
        break;

    case WM_LBUTTONUP:
        m_MyApplicationPtr->LeftMouseButtonAction(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), true);
        InvalidateRect(hWnd, nullptr, true);
        break;

    case WM_RBUTTONUP:
        m_MyApplicationPtr->RightMouseButtonAction(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), true);
        InvalidateRect(hWnd, nullptr, true);
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            m_hDC = BeginPaint(hWnd, &ps);

            m_MyApplicationPtr->Paint();

            EndPaint(hWnd, &ps);
        }
        break;

    case WM_DESTROY:
        delete m_MyApplicationPtr;

        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

void MyEngine::SetColor(COLORREF color)
{
    m_Color = color;
}

void MyEngine::FillEllipse(int x1, int y1, int radiusX, int radiusY)
{
    HBRUSH brush = CreateSolidBrush(m_Color);
    HBRUSH oldBrush = (HBRUSH)SelectObject(m_hDC, brush);

    Ellipse(m_hDC, x1 - radiusX / 2, y1 - radiusY / 2, x1 + radiusX / 2, y1 + radiusY / 2);

    SelectObject(m_hDC, oldBrush);
    DeleteObject(brush);
}

void MyEngine::DrawLine(int x1, int y1, int x2, int y2)
{
    HPEN pen = CreatePen(PS_SOLID, 1, m_Color);
    HPEN oldPen = (HPEN)SelectObject(m_hDC, pen);

    MoveToEx(m_hDC, x1, y1, 0);
    LineTo(m_hDC, x2, y2);

    SelectObject(m_hDC, oldPen);
    DeleteObject(pen);
}

void MyEngine::SetTitle(const std::wstring& text)
{
    SendMessage(m_hWnd, WM_SETTEXT, 0, (LPARAM) text.c_str());
}
