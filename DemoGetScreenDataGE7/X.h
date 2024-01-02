//-----------------------------------------------------------------
// Main Game  File
// C++ Header - X.h - version v7_02			
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Resource.h"	
#include "GameEngine.h"
#include "AbstractGame.h"

#include <memory>
using std::unique_ptr;
//-----------------------------------------------------------------
// Structs and Enum Classes
//-----------------------------------------------------------------
enum class ScanState
{
	Paused, Scanning, Alert
};

//-----------------------------------------------------------------
// X Class																
//-----------------------------------------------------------------
class X : public AbstractGame, public Callable
{
public:				
	//---------------------------
	// Constructor(s) and Destructor
	//---------------------------
	X();

	virtual ~X() override;

	//---------------------------
	// Disabling copy/move constructors and assignment operators   
	//---------------------------
	X(const X& other) = delete;
	X(X&& other) noexcept = delete;
	X& operator=(const X& other) = delete;
	X& operator=(X&& other) noexcept = delete;

	//---------------------------
	// General Methods
	//---------------------------
	void Initialize(HINSTANCE hInstance) override;
	void Start() override;
	void End() override;
	void Paint(RECT rect) override;
	void Tick() override;
	void MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam) override;
	void MouseWheelAction(int x, int y, int distance, WPARAM wParam) override;
	void MouseMove(int x, int y, WPARAM wParam) override;
	void CheckKeyboard() override;
	void KeyPressed(TCHAR cKey) override;
	
	void CallAction(Caller* callerPtr) override;

	//---------------------------
	// My Functions
	//---------------------------
	void InitializeViewBuffer();
	void GetScreenData();
	bool DetectRed();

private:
	// -------------------------
	// Constants
	// -------------------------
	const COLORREF RGB_BLACK		{ RGB(  0, 0, 0) };
	const COLORREF RGB_RED			{ RGB(255, 0, 0) };
	const COLORREF RGB_DARKRED		{ RGB( 91, 0, 0) };
	
	// const unsigned int COLOR_TO_COMPARE	{ 0xFFFF0000 };
	const unsigned int COLOR_TO_COMPARE	{ 0xFF664CFF };
	
	// -------------------------
	// Datamembers
	// -------------------------
	unique_ptr<Button>			m_BtnRedAlertUPtr;
	unique_ptr<Audio>			m_AudioAlertUPtr;

	ScanState m_ProgramState	{ ScanState::Paused };
	int m_ViewWidth { -1 };
	int m_ViewHeight { -1 };

	BYTE* m_ViewDataPtr;

};
