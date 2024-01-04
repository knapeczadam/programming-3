//-----------------------------------------------------------------
// AbstractGame Object
// C++ Header - AbstractGame.h - version v7_01
//
// AbstractGame is the abstract class which defines the functions that a 
// game class can implement for use with the game engine
//-----------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>

//-----------------------------------------------------------------
// AbstractGame Class
//-----------------------------------------------------------------
class AbstractGame
{
public : 	
	AbstractGame() 
	{
		// nothing to create
	}

	virtual ~AbstractGame() 
	{
		// nothing to destroy
	}

	// Disabling copy/move constructors and assignment operators   
	AbstractGame(const AbstractGame& other)					= delete;
	AbstractGame(AbstractGame&& other) noexcept				= delete;
	AbstractGame& operator=(const AbstractGame& other)		= delete;
	AbstractGame& operator=(AbstractGame&& other) noexcept	= delete;

	// Game functions
	virtual void Initialize(HINSTANCE hInstance);												// implemented in the .cpp file
	virtual void Start(void) {}																	// empty definition
	virtual void End(void) {}																	// empty definition
	virtual void MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam) {}	// empty definition
	virtual void MouseWheelAction(int x, int y, int distance, WPARAM wParam) {}					// empty definition
	virtual void MouseMove(int x, int y, WPARAM wParam) {}										// empty definition
	virtual void CheckKeyboard(void) {}															// empty definition
	virtual void KeyPressed(TCHAR cKey) {}														// empty definition
	virtual void Paint(RECT rect) {}															// empty definition
	virtual void Tick() {}																		// empty definition
};