//-----------------------------------------------------------------
// Main Game File
// C++ Source - X.cpp - version v7_02
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "X.h"

#include <filesystem>
#include <regex>

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
	GAME_ENGINE->SetWidth(1024);
	GAME_ENGINE->SetHeight(768);
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
	m_TxtUPtr = std::make_unique<TextBox>();
	m_TxtUPtr->SetBounds(25, 25, 100, 25);
	m_TxtUPtr->Show();
	
	m_BtnUniqueUPtr = std::make_unique<Button>(_T("Load Bitmap"));
	m_BtnUniqueUPtr->SetBounds(150, 25, 100, 25);
	m_BtnUniqueUPtr->AddActionListener(this);
	m_BtnUniqueUPtr->Show();
}

void X::End()
{
	// Insert the code that needs to be executed at the closing of the game
}

void X::Paint(RECT rect)
{
	// Insert paint code
	if (m_BmpPtr)
	{
		const auto bmpWidth = m_BmpPtr->GetWidth();
		const auto bmpHeight = m_BmpPtr->GetHeight();
		// center bmp
		GAME_ENGINE->DrawBitmap(m_BmpPtr.get(), (GAME_ENGINE->GetWidth() - bmpWidth) / 2, (GAME_ENGINE->GetHeight() - bmpHeight) / 2);
		
	}
}

void X::Tick()
{
	// Insert non-paint code that needs to be executed each tick 
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
	if (callerPtr == m_BtnUniqueUPtr.get()) {
		m_Message = m_TxtUPtr->GetText();
        try
        {
        	// check if file exists
        	if (not std::filesystem::exists(m_Message))
			{
				throw BitmapMissingFileException(m_Message);
			}
			if (IsValidImageFileName(m_Message))
			{
				// load bitmap
				// release old bitmap
				m_BmpPtr.reset();
				m_BmpPtr = std::make_unique<Bitmap>(m_Message, true);
			}
			else
			{
				throw BitmapUnsupportedFormatException(m_Message);
			}
        }
		catch (const BitmapMissingFileException& e)
		{
			GAME_ENGINE->MessageBox(e.GetMessage());
		}
        catch (const BitmapUnsupportedFormatException& e)
        {
			GAME_ENGINE->MessageBox(e.GetMessage());
        }
		
		
		
    }
}

bool X::IsValidBmpFileName(const tstring& fileName) const
{
        tregex pattern(_T("^.*.bmp"));
        return std::regex_match(fileName, pattern);
}

bool X::IsValidTgaFileName(const tstring& fileName) const
{
        tregex pattern(_T("^.*.tga"));
        return std::regex_match(fileName, pattern);
}

bool X::IsValidPngFileName(const tstring& fileName) const
{
        tregex pattern(_T("^.*.png"));
        return std::regex_match(fileName, pattern);
}

bool X::IsValidImageFileName(const tstring& fileName) const
{
	return IsValidBmpFileName(fileName) or IsValidTgaFileName(fileName) or IsValidPngFileName(fileName);
}





