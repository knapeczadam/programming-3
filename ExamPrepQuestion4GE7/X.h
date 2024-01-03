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

private:
	void ReadDataFromFile();
	bool IsInteger(const tstring& str, int& number) const;
	bool IsFloatingPoint(const tstring& str, float& number) const;
	std::pair<bool, std::pair<std::optional<int>, std::optional<float>>> IsNumber(const tstring& str) const;

private:
	// -------------------------
	// Datamembers
	// -------------------------
	std::unique_ptr<Button> m_BtnUniqueUPtr;
	std::unique_ptr<Button> m_BtnGreaterUPtr;

	std::unique_ptr<TextBox> m_TxtUPtr;

	std::unique_ptr<Font> m_FontUPtr;

	std::vector<int> m_VecIntegers;

	tstring m_Message;


};