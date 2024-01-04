//-----------------------------------------------------------------
// Project File
// C++ Source - SmartPointersDemo.cpp - version v7_01	
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "SmartPointersDemo.h"		

//-----------------------------------------------------------------
// Exception Classes
//-----------------------------------------------------------------

class DivisionByZeroException final
{};

class IndivisibleException final
{
public:
	IndivisibleException(int remainder) : m_Remainder(remainder)
	{}

	tstring GetErrorMessage() const
	{
		tstringstream buffer;
		buffer << _T("Error: Indivisible. The remainder would be ") << m_Remainder << ".";
		return buffer.str();
	}

private:
	int m_Remainder;
};

//-----------------------------------------------------------------
// SmartPointersDemo methods																				
//-----------------------------------------------------------------

SmartPointersDemo::SmartPointersDemo() 																	
{
	// nothing to create
}

SmartPointersDemo::~SmartPointersDemo()																						
{
	// nothing to destroy
}


void SmartPointersDemo::Initialize(HINSTANCE hInstance)			
{
	// Set the required values
	AbstractGame::Initialize(hInstance);
	GAME_ENGINE->SetTitle(_T("SmartPointersDemo Demo"));					
	GAME_ENGINE->RunGameLoop(true);		
	
	// Set the optional values
	GAME_ENGINE->SetWidth(1024);
	GAME_ENGINE->SetHeight(768);
    GAME_ENGINE->SetFrameRate(50);

	// Set the keys that the project needs to listen to
	//tstringstream buffer;
	//buffer << _T("KLMO");
	//buffer << (TCHAR) VK_LEFT;
	//buffer << (TCHAR) VK_RIGHT;
	//GAME_ENGINE->SetKeyList(buffer.str());
}

void SmartPointersDemo::Start()
{
	m_TxtNumeratorUPtr = make_unique<TextBox>();			
	m_TxtNumeratorUPtr->SetBounds(25, 25, 100, 25);
	m_TxtNumeratorUPtr->Show();

	m_TxtDenominatorUPtr = make_unique<TextBox>();
	m_TxtDenominatorUPtr->SetBounds(25, 60, 100, 25);
	m_TxtDenominatorUPtr->Show();

	m_BtnIntegerDivisionUPtr = make_unique<Button>(_T("Divide"));
	m_BtnIntegerDivisionUPtr->SetBounds(25, 120, 80, 25);
	m_BtnIntegerDivisionUPtr->AddActionListener(this);
	m_BtnIntegerDivisionUPtr->Show();

	m_FontUPtr = make_unique<Font>(_T("Verdana"), false, false, false, 25);
}

void SmartPointersDemo::End()
{
	// Insert the code that needs to be executed at the closing of the project
}

void SmartPointersDemo::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
{	
	// Insert the code that needs to be executed when the project registers a mouse button action

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

void SmartPointersDemo::MouseWheelAction(int x, int y, int distance, WPARAM wParam)
{	
	// Insert the code that needs to be executed when the project registers a mouse wheel action
}

void SmartPointersDemo::MouseMove(int x, int y, WPARAM wParam)
{	
	// Insert the code that needs to be executed when the mouse pointer moves across the project window

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

void SmartPointersDemo::CheckKeyboard()
{	
	// Here you can check if a key of choice is held down
	// Is executed once per frame if the Project Loop is running 

	/* Example:
	if (GAME_ENGINE->IsKeyDown(_T('K'))) xIcon -= xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('L'))) yIcon += xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('M'))) xIcon += xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('O'))) yIcon -= ySpeed;
	*/
}

void SmartPointersDemo::KeyPressed(TCHAR cKey)
{	
	// DO NOT FORGET to use SetKeyList() !!

	// Insert the code that needs to be executed when a key of choice is pressed
	// Is executed as soon as the key is released
	// You first need to specify the keys that the research engine needs to watch by using the SetKeyList() method

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

void SmartPointersDemo::Paint(RECT rect)
{
	GAME_ENGINE->DrawSolidBackground(RGB(227, 227, 227));

	GAME_ENGINE->SetFont(m_FontUPtr.get());
	GAME_ENGINE->SetColor(RGB(27, 27, 27));
	
	GAME_ENGINE->DrawString(_T("Numerator"), 130, 25);
	GAME_ENGINE->DrawString(_T("Denominator"), 130, 60);

	GAME_ENGINE->DrawString(m_Message, 350, 350);
}

void SmartPointersDemo::Tick()
{
	// Insert non-paint code that needs to be executed each tick 
}

int IntegerDivision(int numerator, int denominator) 
{
	if (denominator == 0) throw DivisionByZeroException();
	if (numerator % denominator != 0) throw IndivisibleException(numerator % denominator);

	return numerator / denominator;
}

void SmartPointersDemo::CallAction(Caller* callerPtr)
{
	if (callerPtr == m_BtnIntegerDivisionUPtr.get())	// button is clicked
	{
		int numerator{}, denominator{};

		/////////////////////////
		// clear the previous results
		/////////////////////////
		m_Message = _T("");				
		m_TxtNumeratorUPtr->SetBackcolor(RGB(255, 255, 255));
		m_TxtDenominatorUPtr->SetBackcolor(RGB(255, 255, 255));

		/////////////////////////
		// handle the first textbox
		/////////////////////////
		try
		{
			tstring txtNumerator = m_TxtNumeratorUPtr->GetText();
			numerator = std::stoi(txtNumerator);
		}
		catch (...) // conversion error first textbox
		{
			m_TxtNumeratorUPtr->SetBackcolor(RGB(255, 127, 127));
			return;
		}

		/////////////////////////
		// handle the second textbox
		/////////////////////////
		try
		{
			tstring txtDenominator	= m_TxtDenominatorUPtr->GetText();
			denominator = std::stoi(txtDenominator);
		}
		catch (...) // conversion error second textbox
		{
			m_TxtDenominatorUPtr->SetBackcolor(RGB(255, 127, 127));
			return;
		}

		/////////////////////////
		// evaluate the results
		/////////////////////////
		try
		{
			tstringstream buffer; 
			buffer << _T("Division result is ") << IntegerDivision(numerator, denominator) << _T(".");

			m_Message = buffer.str();
		}
		catch (const DivisionByZeroException&)
		{
			m_Message = _T("Error: division by zero.");
		}
		catch (const IndivisibleException& exception)
		{
			m_Message = exception.GetErrorMessage();
		}
	}
}