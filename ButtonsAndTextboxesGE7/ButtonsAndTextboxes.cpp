//-----------------------------------------------------------------
// Main Game File
// C++ Source - X.cpp - version v7_02
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "ButtonsAndTextboxes.h"																				

//-----------------------------------------------------------------
// X methods																				
//-----------------------------------------------------------------

ButtonsAndTextboxes::ButtonsAndTextboxes() 																	
{
	// nothing to create
}

ButtonsAndTextboxes::~ButtonsAndTextboxes()																						
{
	// nothing to destroy
}


void ButtonsAndTextboxes::Initialize(HINSTANCE hInstance)			
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

void ButtonsAndTextboxes::Start()
{
	// Insert the code that needs to be executed at the start of the game
	m_TxtInputPtr = new TextBox();
	m_TxtInputPtr->SetBounds(25, 25, 100, 45);
	m_TxtInputPtr->AddActionListener(this);
	m_TxtInputPtr->SetFont(_T("Verdana"), false, false, false, 45);
	m_TxtInputPtr->Show();

	m_BtnClickPtr = new Button(_T("Click me"));
	m_BtnClickPtr->SetBounds(150, 25, 100, 45);
	m_BtnClickPtr->AddActionListener(this);
	m_TxtInputPtr->SetFont(_T("Verdana"), false, false, false, 45);
	m_BtnClickPtr->Show();

	
}

void ButtonsAndTextboxes::End()
{
	// Insert the code that needs to be executed at the closing of the game
	delete m_TxtInputPtr;
	delete m_BtnClickPtr;
}

void ButtonsAndTextboxes::Paint(RECT rect)
{
	// Insert paint code
	GAME_ENGINE->SetColor(RGB(255, 255, 255));
	GAME_ENGINE->DrawString(m_Message, 300, 300);
}

void ButtonsAndTextboxes::Tick()
{
	// Insert non-paint code that needs to be executed each tick 
}

void ButtonsAndTextboxes::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
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


void ButtonsAndTextboxes::MouseWheelAction(int x, int y, int distance, WPARAM wParam)
{	
	// Insert the code that needs to be executed when the game registers a mouse wheel action
}

void ButtonsAndTextboxes::MouseMove(int x, int y, WPARAM wParam)
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

void ButtonsAndTextboxes::CheckKeyboard()
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

void ButtonsAndTextboxes::KeyPressed(TCHAR cKey)
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

void ButtonsAndTextboxes::CallAction(Caller* callerPtr)
{
	// Insert the code that needs to be executed when a Caller has to perform an action
	//GAME_ENGINE->MessageBox(_T("Button clicked"));
	// if (callerPtr == m_BtnClickPtr)
	// {
	// 	m_TxtInputPtr->SetText(_T("Clicked"));
	// }
	// else if (callerPtr == m_TxtInputPtr)
	// {
	// 	m_TxtInputPtr->SetText(_T("42"));
	// 	// m_BtnClickPtr->SetText(m_TxtInputPtr->GetText());
	// }
	m_Message = m_TxtInputPtr->GetText();
}




