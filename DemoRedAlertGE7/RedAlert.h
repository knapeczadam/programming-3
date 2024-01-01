//-----------------------------------------------------------------
// Main Game  File
// C++ Header - RedAlert.h - version v7_02			
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
// RedAlert Class																
//-----------------------------------------------------------------
class RedAlert : public AbstractGame, public Callable
{
public:				
	//---------------------------
	// Constructor(s) and Destructor
	//---------------------------
	RedAlert();

	virtual ~RedAlert() override;

	//---------------------------
	// Disabling copy/move constructors and assignment operators   
	//---------------------------
	RedAlert(const RedAlert& other) = delete;
	RedAlert(RedAlert&& other) noexcept = delete;
	RedAlert& operator=(const RedAlert& other) = delete;
	RedAlert& operator=(RedAlert&& other) noexcept = delete;

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

	const unsigned int PIXEL_RED	{ 0xFFFF0000 };

	// -------------------------
	// Datamembers
	// -------------------------
	unique_ptr<Button>			m_BtnRedAlertUPtr;
	unique_ptr<Audio>			m_AudioAlertUPtr;

	ScanState m_ProgramState	{ ScanState::Paused };

	int m_ViewWidth				{ -1 };
	int m_ViewHeight			{ -1 };

	unique_ptr<unsigned int[]>  m_ViewDataUPtr;
};
