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

//-----------------------------------------------------------------
// X Class																
//-----------------------------------------------------------------
class ExceptionsEngineDemo : public AbstractGame, public Callable
{
public:				
	//---------------------------
	// Constructor(s) and Destructor
	//---------------------------
	ExceptionsEngineDemo();

	virtual ~ExceptionsEngineDemo() override;

	//---------------------------
	// Disabling copy/move constructors and assignment operators   
	//---------------------------
	ExceptionsEngineDemo(const ExceptionsEngineDemo& other) = delete;
	ExceptionsEngineDemo(ExceptionsEngineDemo&& other) noexcept = delete;
	ExceptionsEngineDemo& operator=(const ExceptionsEngineDemo& other) = delete;
	ExceptionsEngineDemo& operator=(ExceptionsEngineDemo&& other) noexcept = delete;

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

private:
	// -------------------------
	// Datamembers
	// -------------------------
	Bitmap* m_BmpPtr = nullptr;
	TextBox* m_TextBoxPtr = nullptr;


};
