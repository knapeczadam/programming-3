//-----------------------------------------------------------------
// Game File
// C++ Header - Soundboard.h 
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Resource.h"	
#include "GameEngine.h"
#include "AbstractGame.h"

#include "Slider.h"

//-----------------------------------------------------------------
// Soundboard Class																
//-----------------------------------------------------------------
class Soundboard : public AbstractGame, public Callable
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	Soundboard() = default;

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Soundboard() override = default;

	// Disabling copy/move constructors and assignment operators   
	Soundboard(const Soundboard& other)					= delete;
	Soundboard(Soundboard&& other) noexcept				= delete;
	Soundboard& operator=(const Soundboard& other)		= delete;
	Soundboard& operator=(Soundboard&& other) noexcept	= delete;

	//---------------------------
	// General Methods
	//---------------------------
	void Initialize(HINSTANCE hInstance);
	void Start();				
	void End();
	void MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam);
	void MouseMove(int x, int y, WPARAM wParam);
	void CheckKeyboard();
	void Tick();
	void Paint(RECT rect);

	void CallAction(Caller* callerPtr);

	//---------------------------
	// Constants
	//---------------------------

	static const int STARTVOLUME_RAIN		{  1 };
	static const int STARTVOLUME_METROPOLIS	{ 60 };
	static const int STARTVOLUME_FIST		{  1 };

private:
	// -------------------------
	// Datamembers
	// -------------------------
	Bitmap* m_BmpSliderPtr{}, *m_BmpButtonPtr{}, *m_BmpLightbarPtr{}, *m_BmpBgPtr{};
	Audio* m_Mp3RainPtr{}, *m_Mp3MetropolisPtr{}, *m_Mp3FistPtr{};
	
	bool m_AudioLoaded{};

	Slider* m_SliderMetropolisPtr{}, * m_SliderRainPtr{}, * m_SliderFistPtr{};

	Font* m_FontPtr{};
};
