#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------
// Slider Class									
//-----------------------------------------------------
class Slider final
{
public:
	Slider(int x, int y, Bitmap* bmpSliderPtr, Bitmap* bmpButtonPtr, Bitmap* bmpLightbarPtr, Audio* m_AudioPtr, int audioVolume);				// Constructor
	~Slider() = default;		// Nothing to destroy
		
	// Disabling copy/move constructors and assignment operators   
	Slider(const Slider& other)					= delete;
	Slider(Slider&& other) noexcept				= delete;
	Slider& operator=(const Slider& other)		= delete;
	Slider& operator=(Slider&& other) noexcept	= delete;

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Tick();
	void Paint();
	void ChangeVolume(int delta);
	void MouseButtonAction(bool isLeft, bool isDown, int x, int y);
	void MouseMove(int x, int y);
	void UpdateButton();
	
	//-------------------------------------------------
	// Constants								
	//-------------------------------------------------
	static const int TOTALHEIGHT		= 212;
	static const int SLIDERHEIGHT		= 155;

	static const int OFFSET_X_BUTTON	=   5;
	static const int OFFSET_X_LIGHTBAR	=  80;
	static const int OFFSET_X_FILL		=   3;

	static const int OFFSET_Y_SLIDER	=  60;

	static const int FILLWIDTH			=   3;

	static const int MAXVOLUME			= 100;

private: 
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	Bitmap* m_BmpSliderPtr{}, * m_BmpButtonPtr{}, * m_BmpLightbarPtr{};
	Audio* m_AudioPtr{};

	int m_X{}, m_Y{}, m_YButton{};
	bool m_Clicked{};
	int m_DeltaYClick{};
	
	int m_Volume{};
	bool m_SoundChanged{};
};

 
