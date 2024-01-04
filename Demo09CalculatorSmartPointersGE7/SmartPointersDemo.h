//-----------------------------------------------------------------
// Project File
// C++ Header - SmartPointersDemo.h - version v7_01	
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Resource.h"	
#include "GameEngine.h"
#include "AbstractGame.h"

//-----------------------------------------------------------------
// SmartPointersDemo Class																
//-----------------------------------------------------------------
class SmartPointersDemo : public AbstractGame, public Callable
{
public:				
	//---------------------------
	// Constructor(s) and Destructor
	//---------------------------
	SmartPointersDemo();

	virtual ~SmartPointersDemo();

	// Disabling copy/move constructors and assignment operators   
	SmartPointersDemo(const SmartPointersDemo& other)					= delete;
	SmartPointersDemo(SmartPointersDemo&& other) noexcept				= delete;
	SmartPointersDemo& operator=(const SmartPointersDemo& other)		= delete;
	SmartPointersDemo& operator=(SmartPointersDemo&& other) noexcept	= delete;

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
	unique_ptr<TextBox> m_TxtNumeratorUPtr, m_TxtDenominatorUPtr;
	unique_ptr<Button>	m_BtnIntegerDivisionUPtr;
	unique_ptr<Font>	m_FontUPtr;

	tstring m_Message;
};
