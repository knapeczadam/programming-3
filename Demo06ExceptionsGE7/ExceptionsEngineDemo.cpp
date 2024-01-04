//-----------------------------------------------------------------
// Main Game File
// C++ Source - X.cpp - version v7_02
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "ExceptionsEngineDemo.h"

//-----------------------------------------------------------------
// X methods																				
//-----------------------------------------------------------------

ExceptionsEngineDemo::ExceptionsEngineDemo() 																	
{
	// nothing to create
}

ExceptionsEngineDemo::~ExceptionsEngineDemo()																						
{
	// nothing to destroy
	delete m_BmpPtr;
	delete m_TextBoxPtr;
}


void ExceptionsEngineDemo::Initialize(HINSTANCE hInstance)			
{
	// Set the required values
	AbstractGame::Initialize(hInstance);
	GAME_ENGINE->SetTitle(_T("Game Engine version 7_02"));					
	GAME_ENGINE->RunGameLoop(true);

	// load bitmap
	try
	{
		m_BmpPtr = new Bitmap(_T("dociu.bmp"));
	}
	catch (const BitmapNotLoadedException& e)
	{
		GAME_ENGINE->MessageBox(_T(" Bitmap not found."));
	}
	// if (not m_BmpPtr->Exists()) GAME_ENGINE->MessageBox(_T("Bitmap not found."));
	
	// Set the optional values
	GAME_ENGINE->SetWidth(m_BmpPtr->GetWidth());
	GAME_ENGINE->SetHeight(m_BmpPtr->GetHeight());
    GAME_ENGINE->SetFrameRate(50);

	// Set the keys that the game needs to listen to
	//tstringstream buffer;
	//buffer << _T("KLMO");
	//buffer << (TCHAR) VK_LEFT;
	//buffer << (TCHAR) VK_RIGHT;
	//GAME_ENGINE->SetKeyList(buffer.str());
}

void ExceptionsEngineDemo::Start()
{
	// Insert the code that needs to be executed at the start of the game
	m_TextBoxPtr = new TextBox();
	m_TextBoxPtr->SetBounds(25, 25, 100, 25);
	m_TextBoxPtr->AddActionListener(this);
	m_TextBoxPtr->Show();
}

void ExceptionsEngineDemo::End()
{
	// Insert the code that needs to be executed at the closing of the game
}

void ExceptionsEngineDemo::Paint(RECT rect)
{
	// Insert paint code
	GAME_ENGINE->DrawBitmap(m_BmpPtr, 0, 0);
}

void ExceptionsEngineDemo::Tick()
{
	// Insert non-paint code that needs to be executed each tick 
}

void ExceptionsEngineDemo::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
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


void ExceptionsEngineDemo::MouseWheelAction(int x, int y, int distance, WPARAM wParam)
{	
	// Insert the code that needs to be executed when the game registers a mouse wheel action
}

void ExceptionsEngineDemo::MouseMove(int x, int y, WPARAM wParam)
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

void ExceptionsEngineDemo::CheckKeyboard()
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

void ExceptionsEngineDemo::KeyPressed(TCHAR cKey)
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

void ExceptionsEngineDemo::CallAction(Caller* callerPtr)
{
	// Insert the code that needs to be executed when a Caller has to perform an action
	// GAME_ENGINE->MessageBox(_T("Enter pressed in textbox"));

	if (callerPtr == m_TextBoxPtr)
	{
		int number{};
		// convert and handle exceptions
		try
		{
			number = std::stoi(m_TextBoxPtr->GetText());
			GAME_ENGINE->MessageBox(_T("Number entered: ") + m_TextBoxPtr->GetText());
		}
		catch (...) // catch all exceptions
		{
			GAME_ENGINE->MessageBox(_T("Invalid argument."));
			m_TextBoxPtr->SetBackcolor(RGB(255, 0, 0));
			m_TextBoxPtr->SetText(_T(""));
		}
		// catch (const std::invalid_argument& e)
		// {
		// 	GAME_ENGINE->MessageBox(_T("Invalid argument."));
		// 	m_TextBoxPtr->SetBackcolor(RGB(255, 0, 0));
		// 	m_TextBoxPtr->SetText(_T(""));
		// }
		// catch (const std::out_of_range& e)
		// {
		// 	GAME_ENGINE->MessageBox(_T("Out of range."));
		// 	m_TextBoxPtr->SetBackcolor(RGB(255, 0, 0));
		// 	m_TextBoxPtr->SetText(_T(""));
		// }
		// catch (...)
		// {
		// 	GAME_ENGINE->MessageBox(_T("Unknown exception."));
		// 	m_TextBoxPtr->SetBackcolor(RGB(255, 0, 0));
		// 	m_TextBoxPtr->SetText(_T(""));
		// }
	}
	
}




