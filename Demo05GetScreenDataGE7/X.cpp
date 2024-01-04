//-----------------------------------------------------------------
// Main Game File
// C++ Source - X.cpp - version v7_02
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "X.h"
using std::make_unique;

//-----------------------------------------------------------------
// X methods																				
//-----------------------------------------------------------------

X::X() 																	
{
    // nothing to create
}

X::~X()																						
{
    // nothing to destroy
}


void X::Initialize(HINSTANCE hInstance)			
{
    // Set the required values
    AbstractGame::Initialize(hInstance);
    GAME_ENGINE->SetTitle(_T("Game Engine version 7_02"));					
    GAME_ENGINE->RunGameLoop(true);		
    
    // Set the optional values
    GAME_ENGINE->SetWidth(250);
    GAME_ENGINE->SetHeight(75);
    GAME_ENGINE->SetFrameRate(50);

    // Set the keys that the game needs to listen to
    //tstringstream buffer;
    //buffer << _T("KLMO");
    //buffer << (TCHAR) VK_LEFT;
    //buffer << (TCHAR) VK_RIGHT;
    //GAME_ENGINE->SetKeyList(buffer.str());
}

void X::Start()
{
    // Insert the code that needs to be executed at the start of the game
    constexpr int BUTTON_WIDTH{120};

    m_BtnRedAlertUPtr = make_unique<Button>(_T("Arm"));
    m_BtnRedAlertUPtr->SetBounds((GAME_ENGINE->GetWidth() - BUTTON_WIDTH) / 2, 25, BUTTON_WIDTH, 25);
    m_BtnRedAlertUPtr->AddActionListener(this);
    m_BtnRedAlertUPtr->Show();

    m_AudioAlertUPtr = make_unique<Audio>(_T("Audio/siren.mp3"));
    m_AudioAlertUPtr->SetRepeat(true);
}

void X::End()
{
    // Insert the code that needs to be executed at the closing of the game
    delete m_ViewDataPtr;
}

void X::Paint(RECT rect)
{
    switch (m_ProgramState)
    {
    case ScanState::Scanning:
        GAME_ENGINE->DrawSolidBackground(RGB_DARKRED);
        break;
    case ScanState::Alert:
        GAME_ENGINE->DrawSolidBackground(RGB_RED);
        break;
    default:
        GAME_ENGINE->DrawSolidBackground(RGB_BLACK);
    }
}

void X::Tick()
{
    m_AudioAlertUPtr->Tick();

    switch (m_ProgramState)
    {
    case ScanState::Scanning:
        GetScreenData();

        if (DetectRed())
        {
            m_ProgramState = ScanState::Alert;
            m_BtnRedAlertUPtr->SetText(_T("Disarm"));
            m_AudioAlertUPtr->Play();
        }
    }
}

void X::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
{	
    // Insert the code that needs to be executed when the game registers a mouse button action

    /* Example:
    if (isLeft == true && isDown == true) // is it a left mouse click?
    {	
        if ( x > 261 && x < 261 + 117 ) // check if click lies within x coordinates of choice
        {
            if ( y > 182 && y < 182 + 33 ) // check if click also lies within y coordinates of choice
            {
                GAME_ENGINE->MessageBox(_T("Clicked."));
            }
        }
    }
    */
}


void X::MouseWheelAction(int x, int y, int distance, WPARAM wParam)
{	
    // Insert the code that needs to be executed when the game registers a mouse wheel action
}

void X::MouseMove(int x, int y, WPARAM wParam)
{	
    // Insert the code that needs to be executed when the mouse pointer moves across the game window

    /* Example:
    if ( x > 261 && x < 261 + 117 ) // check if mouse position is within x coordinates of choice
    {
        if ( y > 182 && y < 182 + 33 ) // check if mouse position also is within y coordinates of choice
        {
            GAME_ENGINE->MessageBox(_T("Da mouse wuz here."));
        }
    }
    */
}

void X::CheckKeyboard()
{	
    // Here you can check if a key of choice is held down
    // Is executed once per frame if the Game Loop is running 

    /* Example:
    if (GAME_ENGINE->IsKeyDown(_T('K'))) xIcon -= xSpeed;
    if (GAME_ENGINE->IsKeyDown(_T('L'))) yIcon += xSpeed;
    if (GAME_ENGINE->IsKeyDown(_T('M'))) xIcon += xSpeed;
    if (GAME_ENGINE->IsKeyDown(_T('O'))) yIcon -= ySpeed;
    */
}

void X::KeyPressed(TCHAR cKey)
{	
    // DO NOT FORGET to use SetKeyList() !!

    // Insert the code that needs to be executed when a key of choice is pressed
    // Is executed as soon as the key is released
    // You first need to specify the keys that the game engine needs to watch by using the SetKeyList() method

    /* Example:
    switch (cKey)
    {
    case _T('K'): case VK_LEFT:
        GAME_ENGINE->MessageBox(_T("Moving left."));
        break;
    case _T('L'): case VK_DOWN:
        GAME_ENGINE->MessageBox(_T("Moving down."));
        break;
    case _T('M'): case VK_RIGHT:
        GAME_ENGINE->MessageBox(_T("Moving right."));
        break;
    case _T('O'): case VK_UP:
        GAME_ENGINE->MessageBox(_T("Moving up."));
        break;
    case VK_ESCAPE:
        GAME_ENGINE->MessageBox(_T("Escape menu."));
    }
    */
}

void X::CallAction(Caller* callerPtr)
{
    // Insert the code that needs to be executed when a Caller has to perform an action
    switch (m_ProgramState)
    {
    case ScanState::Paused:
        InitializeViewBuffer();

        m_ProgramState = ScanState::Scanning;
        m_BtnRedAlertUPtr->SetText(_T("Scanning"));

        break;
    case ScanState::Alert:
        m_AudioAlertUPtr->Stop();

    default:
        m_ProgramState = ScanState::Paused;
        m_BtnRedAlertUPtr->SetText(_T("Arm"));
    }
}

void X::InitializeViewBuffer()
{
    m_ViewWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    m_ViewHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN);

    m_ViewDataPtr = new BYTE[m_ViewWidth * m_ViewHeight * 4];
}

void X::GetScreenData()
{
    // get the device context of the screen
    HDC hScreenDC = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);

    // and a device context to put it in
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);

    // get a new bitmap
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, m_ViewWidth, m_ViewHeight);

    // copy screen data into the bitmap
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);
    BitBlt(hMemoryDC, 0, 0, m_ViewWidth, m_ViewHeight, hScreenDC, 0, 0, SRCCOPY);
    hBitmap = (HBITMAP)SelectObject(hMemoryDC, hOldBitmap);

    // get the data
    BITMAPINFO Bmi;
    memset(&Bmi, 0, sizeof(BITMAPINFO));
    Bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    Bmi.bmiHeader.biWidth = m_ViewWidth;
    Bmi.bmiHeader.biHeight = m_ViewHeight;
    Bmi.bmiHeader.biPlanes = 1;
    Bmi.bmiHeader.biBitCount = 32;
    Bmi.bmiHeader.biCompression = BI_RGB;
    Bmi.bmiHeader.biSizeImage = m_ViewWidth * m_ViewHeight * 4;

    GetDIBits(hScreenDC, hBitmap, 0, m_ViewHeight, m_ViewDataPtr, (BITMAPINFO*)&Bmi, DIB_RGB_COLORS);

    //// clean up
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    DeleteDC(hScreenDC);
}

bool X::DetectRed()
{
    BYTE* line1Ptr{ m_ViewDataPtr };
    BYTE* line2Ptr{ line1Ptr + m_ViewWidth * 4 };
    BYTE* line3Ptr{ line1Ptr + m_ViewWidth * 2 * 4 };
    BYTE* line4Ptr{ line1Ptr + m_ViewWidth * 3 * 4};
    BYTE* line5Ptr{ line1Ptr + m_ViewWidth * 4 * 4};

    for (int countPixels{}; countPixels < m_ViewWidth * m_ViewHeight; ++countPixels)
    {
        // No automatic conversion from BYTE* to unsigned int*
        // COLOR_TO_COMPARE is stored as ARGB = 0xFFFF0000
        // Color is stored in memory as BB GG RR AA = little endian
        // BGRA8888 
        // https://en.wikipedia.org/wiki/RGBA_color_model
        BYTE alpha = (COLOR_TO_COMPARE >> 24) & 0xFF;
        BYTE red = (COLOR_TO_COMPARE >> 16) & 0xFF;
        BYTE green = (COLOR_TO_COMPARE >> 8) & 0xFF;
        BYTE blue = COLOR_TO_COMPARE & 0xFF;
        
        int offset = countPixels * 4;
        if (m_ViewDataPtr[offset] == blue &&
            m_ViewDataPtr[offset + 1] == green &&
            m_ViewDataPtr[offset + 2] == red &&
            m_ViewDataPtr[offset + 3] == alpha)
        {
            auto currentPixel = m_ViewDataPtr + offset;
            return true;
        }
    }

    return false;
}
