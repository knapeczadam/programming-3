//-----------------------------------------------------------------
// Project File
// C++ Header - ExceptionsDemo.h - version v7_01	
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Resource.h"	
#include "GameEngine.h"
#include "AbstractGame.h"

//-----------------------------------------------------------------
// ExceptionsDemo Class																
//-----------------------------------------------------------------
class ExceptionsDemo : public AbstractGame, public Callable
{
public:				
	//---------------------------
	// Constructor(s) and Destructor
	//---------------------------
	ExceptionsDemo();

	virtual ~ExceptionsDemo();

	// Disabling copy/move constructors and assignment operators   
	ExceptionsDemo(const ExceptionsDemo& other)					= delete;
	ExceptionsDemo(ExceptionsDemo&& other) noexcept				= delete;
	ExceptionsDemo& operator=(const ExceptionsDemo& other)		= delete;
	ExceptionsDemo& operator=(ExceptionsDemo&& other) noexcept	= delete;

	//---------------------------
	// General Methods
	//---------------------------
	virtual void Initialize(HINSTANCE hInstance) override;
	virtual void Start() override;
	virtual void End() override;
	virtual void MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam) override;
	virtual void MouseWheelAction(int x, int y, int distance, WPARAM wParam) override;
	virtual void MouseMove(int x, int y, WPARAM wParam) override;
	virtual void CheckKeyboard() override;
	virtual void KeyPressed(TCHAR cKey) override;
	virtual void Paint(RECT rect) override;
	virtual void Tick() override;
	
	virtual void CallAction(Caller* callerPtr) override;

private:
	// -------------------------
	// Datamembers
	// -------------------------
	TextBox* m_TxtNumeratorPtr{};
	TextBox* m_TxtDenominatorPtr{};
	
	Button* m_BtnIntegerDivisionPtr{};
	
	Font* m_FontPtr{};

	tstring m_Message;
};
