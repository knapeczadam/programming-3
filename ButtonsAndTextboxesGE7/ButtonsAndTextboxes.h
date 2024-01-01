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
class ButtonsAndTextboxes : public AbstractGame, public Callable
{
public:				
	//---------------------------
	// Constructor(s) and Destructor
	//---------------------------
	ButtonsAndTextboxes();

	virtual ~ButtonsAndTextboxes() override;

	//---------------------------
	// Disabling copy/move constructors and assignment operators   
	//---------------------------
	ButtonsAndTextboxes(const ButtonsAndTextboxes& other) = delete;
	ButtonsAndTextboxes(ButtonsAndTextboxes&& other) noexcept = delete;
	ButtonsAndTextboxes& operator=(const ButtonsAndTextboxes& other) = delete;
	ButtonsAndTextboxes& operator=(ButtonsAndTextboxes&& other) noexcept = delete;

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
	TextBox* m_TxtInputPtr{nullptr};
	Button*  m_BtnClickPtr{nullptr};
	tstring  m_Message;


};
