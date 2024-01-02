//-----------------------------------------------------------------
// Main Game File
// C++ Source - RedAlert.cpp - version v7_02
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "RedAlert.h"	
using std::make_unique;

//-----------------------------------------------------------------
// RedAlert methods																				
//-----------------------------------------------------------------

RedAlert::RedAlert() 																	
{
    // nothing to create
}
RedAlert::~RedAlert()																						
{
    // nothing to destroy
}

void RedAlert::Initialize(HINSTANCE hInstance)			
{
    // Set the required values
    AbstractGame::Initialize(hInstance);
    GAME_ENGINE->SetTitle(_T("Red Alert"));					
    GAME_ENGINE->RunGameLoop(true);
    
    // load bitmap
    try
    {
        // m_BmpPtr = new Bitmap(_T("circle.bmp"));
        m_BmpPtr = new Bitmap(_T("cross.bmp"));
        // m_BmpPtr = new Bitmap(_T("square.bmp"));
        // m_BmpPtr = new Bitmap(_T("hourglass.bmp"));
    }
    catch (const BitmapNotLoadedException& e)
    {
        GAME_ENGINE->MessageBox(_T(" Bitmap not found."));
    }
	if (not m_BmpPtr->Exists()) GAME_ENGINE->MessageBox(_T("Bitmap not found."));
    
    // Set the optional values
    GAME_ENGINE->SetWidth(250);
    GAME_ENGINE->SetHeight(75);
    GAME_ENGINE->SetFrameRate(50);

}

void RedAlert::Start()
{
    constexpr int BUTTON_WIDTH{120};

    m_BtnRedAlertUPtr = make_unique<Button>(_T("Arm"));
    m_BtnRedAlertUPtr->SetBounds((GAME_ENGINE->GetWidth() - BUTTON_WIDTH) / 2, 25, BUTTON_WIDTH, 25);
    m_BtnRedAlertUPtr->AddActionListener(this);
    m_BtnRedAlertUPtr->Show();

    m_AudioAlertUPtr = make_unique<Audio>(_T("Audio/siren.mp3"));
    m_AudioAlertUPtr->SetRepeat(true);
}

void RedAlert::End()
{
    // Nothing to destroy
}

void RedAlert::Paint(RECT rect)
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

void RedAlert::Tick()
{
    m_AudioAlertUPtr->Tick();

    switch (m_ProgramState)
    {
    case ScanState::Scanning:
        GetScreenData();

        // if (DetectRed())
        if (DetectRedCross())
        {
            m_ProgramState = ScanState::Alert;
            m_BtnRedAlertUPtr->SetText(_T("Disarm"));
            m_AudioAlertUPtr->Play();
        }
    }
}



bool RedAlert::DetectRed()
{
    unsigned int* line1Ptr{ m_ViewDataUPtr.get() };
    unsigned int* line2Ptr{ line1Ptr + m_ViewWidth };
    unsigned int* line3Ptr{ line1Ptr + m_ViewWidth * 2 };
    unsigned int* line4Ptr{ line1Ptr + m_ViewWidth * 3 };
    unsigned int* line5Ptr{ line1Ptr + m_ViewWidth * 4 };

    for (int countPixels{}; countPixels < m_ViewWidth * m_ViewHeight; ++countPixels)
    {
        // Conversion is automatically done
        // COLOR_TO_COMPARE is stored as ARGB = 0xFFFF0000
        // Color is stored in memory as BB GG RR AA = little endian
        // BGRA8888 
        // https://en.wikipedia.org/wiki/RGBA_color_model
        if (m_ViewDataUPtr[countPixels] == COLOR_TO_COMPARE)
        {
            auto currentPixel = m_ViewDataUPtr[countPixels];
            auto alpha = currentPixel >> 24;
            auto red = (currentPixel >> 16) & 0xFF;
            auto green = (currentPixel >> 8) & 0xFF;
            auto blue = currentPixel & 0xFF;
            return true;
        }

    }

    return false;
}

int RedAlert::GetIndex(int x, int y) const
{
    return y * m_ViewWidth + x;
}


bool RedAlert::DetectRedCross()
{
    unsigned int refColor = 0xFFFF0000;
    unsigned int refAlpha = refColor >> 24;
    unsigned int refRed = (refColor >> 16) & 0xFF;
    unsigned int refGreen = (refColor >> 8) & 0xFF;
    unsigned int refBlue = refColor & 0xFF;
    
    const int bmpWidth = m_BmpPtr->GetWidth();
    const int bmpHeight = m_BmpPtr->GetHeight();
    
    for (int y = 0; y <= m_ViewHeight - bmpHeight; ++y)
    {
        for (int x = 0; x <= m_ViewWidth - bmpWidth; ++x)
        {
            bool isRed = false;
            for (int yImage = 0; yImage < bmpHeight; ++yImage)
            {
                for (int xImage = 0; xImage < bmpWidth; ++xImage)
                {
                    int index = GetIndex(x + xImage, y + yImage);
                    int indexImage = yImage * bmpWidth + xImage;
                    int offset = indexImage * 4;
                    auto blue = (unsigned) m_BmpPtr->GetPixelsPtr()[offset];
                    auto green = (unsigned) m_BmpPtr->GetPixelsPtr()[offset + 1];
                    auto red = (unsigned) m_BmpPtr->GetPixelsPtr()[offset + 2];
                    auto alpha = (unsigned) m_BmpPtr->GetPixelsPtr()[offset + 3];
                    if (red == refRed && green == refGreen && blue == refBlue && alpha == refAlpha)
                    {
                        if (m_ViewDataUPtr[index] == refColor)
                        {
                            isRed = true;
                        }
                        else
                        {
                            isRed = false;
                            break;
                        }
                    }
                    else
                    {
                        if (m_ViewDataUPtr[index] == refColor)
                        {
                            isRed = false;
                            break;
                        }
                    }
                }
                if (not isRed) break;
            }
            if (isRed) return true;
        }
    }
    return false;
}

void RedAlert::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
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
void RedAlert::MouseWheelAction(int x, int y, int distance, WPARAM wParam)
{	
    // Insert the code that needs to be executed when the game registers a mouse wheel action
}
void RedAlert::MouseMove(int x, int y, WPARAM wParam)
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
void RedAlert::CheckKeyboard()
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
void RedAlert::KeyPressed(TCHAR cKey)
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

void RedAlert::CallAction(Caller* callerPtr)
{
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

void RedAlert::InitializeViewBuffer()
{
    m_ViewWidth  = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    m_ViewHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN);

    m_ViewDataUPtr = make_unique<unsigned int[]>(m_ViewWidth * m_ViewHeight); // will call delete[] on the old array
}

void RedAlert::GetScreenData()
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

    GetDIBits(hScreenDC, hBitmap, 0, m_ViewHeight, m_ViewDataUPtr.get(), (BITMAPINFO*) &Bmi, DIB_RGB_COLORS);

    //// clean up
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    DeleteDC(hScreenDC);
}




