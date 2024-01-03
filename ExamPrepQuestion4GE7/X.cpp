//-----------------------------------------------------------------
// Main Game File
// C++ Source - X.cpp - version v7_02
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "X.h"
#include <ranges>
#include <algorithm>
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
	m_BtnUniqueUPtr = std::make_unique<Button>(_T("Unique"));
	m_BtnUniqueUPtr->SetBounds(25, 120, 80, 25);
	m_BtnUniqueUPtr->AddActionListener(this);
	m_BtnUniqueUPtr->Show();

	m_BtnGreaterUPtr = std::make_unique<Button>(_T("Greater"));
	m_BtnGreaterUPtr->SetBounds(25, 150, 80, 25);
	m_BtnGreaterUPtr->AddActionListener(this);
	m_BtnGreaterUPtr->Show();

	m_TxtUPtr = std::make_unique<TextBox>();
	m_TxtUPtr->SetBounds(25, 25, 100, 25);
	m_TxtUPtr->Show();

	m_FontUPtr = std::make_unique<Font>(_T("Verdana"), false, false, false, 25);

	ReadDataFromFile();
}

void X::End()
{
	// Insert the code that needs to be executed at the closing of the game
}

void X::Paint(RECT rect)
{
	// Insert paint code
	GAME_ENGINE->DrawSolidBackground(RGB(127, 127, 127));

	GAME_ENGINE->SetFont(m_FontUPtr.get());
	GAME_ENGINE->SetColor(RGB(255, 255, 255));

	GAME_ENGINE->DrawString(m_Message, 25, 200);
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
        // do something
		m_Message = _T("");
		tstringstream buffer;
		// count unique elements in vector
		std::ranges::sort (m_VecIntegers);
		const size_t uniqueElements = std::unique(m_VecIntegers.begin(), m_VecIntegers.end()) - m_VecIntegers.begin();
		// print unique elements, use std::copy, then flush
		buffer << "The number of unique integers in this dataset is ";
		buffer << uniqueElements;
		m_Message = buffer.str();
		
    }
    else if (callerPtr == m_BtnGreaterUPtr.get()) {
        // do something else
    	// read number from the textbox
    	// accept only numbers
    	// The program should print how many numbers in the dataset are greater than the number in the textbox: “There are x numbers in this dataset that are greater than y.” (fill in x and y).
    	// start
    	m_Message = _T("");
    	tstringstream buffer;
		auto [isNumber, pair] = IsNumber(m_TxtUPtr->GetText());
    	if (isNumber) {
    		auto number = pair.first.has_value() ? pair.first.value() : pair.second.value();
			// count numbers greater than number
			const size_t greaterElements = std::ranges::count_if(m_VecIntegers, [number](int i) { return i > number; });
			// print unique elements, use std::copy, then flush
			buffer << "There are ";
			buffer << greaterElements;
			buffer << " numbers in this dataset that are greater than ";
			buffer << number;
			m_Message = buffer.str();
		}
		else {
			m_Message = _T("Please enter a valid integer");
		}
    }
}

void X::ReadDataFromFile()
{
	// read input.txt, use c++17 filesystem
	// if file not found, throw exception
	// if file found, read data and store in vector, but only integers

	tifstream input{ "input.txt" };
	if (!input.is_open()) {
		throw std::runtime_error{ "file not found" };
	}
	for (tstring line; std::getline(input, line); ) {
		try {
			int number;
			if (IsInteger(line, number)) {
				m_VecIntegers.push_back(number);
			}
		}
		catch (std::invalid_argument&) {
			// ignore
		}
		catch (std::out_of_range&) {
			// ignore
		}
	}
	input.close();
}

bool X::IsInteger(const tstring& str, int& number) const
{
	try {
		size_t pos{};
		number = std::stoi(str, &pos);
		return pos == str.length(); // // If pos is equal to the length of the string, then the entire string was consumed
	}
	catch (std::invalid_argument&) {
		return false; // Conversion to integer failed
	}
	catch (std::out_of_range&) {
		return false; // Value is out of the range for an integer
	}
}

bool X::IsFloatingPoint(const tstring& str, float& number) const
{
	try {
		size_t pos{};
		number = std::stof(str, &pos);
		// string should contain a '.' character
		if (str.find('.') == std::string::npos) {
			return false;
		}
		return pos == str.length(); // // If pos is equal to the length of the string, then the entire string was consumed
	}
	catch (std::invalid_argument&) {
		return false; // Conversion to float failed
	}
	catch (std::out_of_range&) {
		return false; // Value is out of the range for a float
	}
}

std::pair<bool, std::pair<std::optional<int>, std::optional<float>>> X::IsNumber(const tstring& str) const
{
	// use regex
	// return a pair of bool and a pair of optional<int> and optional<float>
	// if bool is true, then the string is a number
	// if bool is false, then the string is not a number
	// if bool is true, then the optional<int> or optional<float> contains the number
	// if bool is false, then the optional<int> or optional<float> is empty
	if ( std::regex_match(str, tregex{ _T("(([\\+\\-]*\\d*\\.*\\d+[eE])?([\\+\\-]*\\d*\\.*\\d+))") }) ) {
		// integer
		int number1;
		if (IsInteger(str, number1)) {
			return { true, { number1, std::nullopt } };
		}
		float number2;
		if (IsFloatingPoint(str, number2)) {
			return { true, { std::nullopt, number2 } };
		}
	}
	return { false, { std::nullopt, std::nullopt } };
}




