#include "MyEngine.h"

#include "resource.h"

HINSTANCE m_Instance;

MyEngine::MyEngine(HINSTANCE hInstance, int nCmdShow, const tstring& title, int width, int height, bool fullscreen)
    : 
     m_Width(width)
    , m_Height(height)
{
    m_Instance = hInstance;
    LoadString(hInstance, IDC_MYENGINE32, (LPTSTR) m_ClassName.c_str(), m_MaxLoadString);
    MyRegisterClass();

    if (not InitInstance(nCmdShow))
    {
        return;
    }
}

MyEngine::~MyEngine()
{
}

int MyEngine::Run()
{
    HACCEL hAccelTable = LoadAccelerators(m_Instance, MAKEINTRESOURCE(IDC_MYENGINE32));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (not TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyEngine::MyRegisterClass()
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = m_Instance;
    wcex.hIcon          = LoadIcon(m_Instance, MAKEINTRESOURCE(IDI_MYENGINE32));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_MYENGINE32);
    wcex.lpszClassName  = m_ClassName.c_str();
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

BOOL MyEngine::InitInstance(int nCmdShow)
{
    HWND hWnd = CreateWindow(m_ClassName.c_str(), m_ClassName.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_Instance, nullptr);

    if (not hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

LRESULT MyEngine::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            
            switch (wmId)
            {
                case IDM_ABOUT:
                    DialogBox(m_Instance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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

INT_PTR MyEngine::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
        case WM_INITDIALOG:
            return (INT_PTR) TRUE;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR) TRUE;
            }
            break;
    }
    return (INT_PTR) FALSE;
}
