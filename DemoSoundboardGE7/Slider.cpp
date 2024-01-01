//---------------------------
// Includes
//---------------------------
#include "Slider.h"

//---------------------------
// Defines
//---------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//---------------------------
// Constructor & Destructor
//---------------------------
Slider::Slider(int x, int y, Bitmap* bmpSliderPtr, Bitmap* bmpButtonPtr, Bitmap* bmpLightbarPtr, Audio* m_AudioPtr, int audioVolume) : 
							m_BmpSliderPtr(bmpSliderPtr), m_BmpButtonPtr(bmpButtonPtr), m_BmpLightbarPtr(bmpLightbarPtr), m_AudioPtr(m_AudioPtr),
							m_X(x), m_Y(y), m_YButton(0),
							m_Volume(audioVolume)
{
	m_AudioPtr->SetVolume(audioVolume);
	m_AudioPtr->SetRepeat(true);
	m_AudioPtr->Play();

	UpdateButton();
}

//---------------------------
// Public methods
//---------------------------
void Slider::Tick()
{
	if (m_SoundChanged == true) 
	{
		m_AudioPtr->SetVolume(m_Volume);
		m_SoundChanged = false;
	}

	m_AudioPtr->Tick();
}

void Slider::Paint()
{
	// calculate bottom of slider
	int bottomSlider{ m_Y + TOTALHEIGHT };

	// draw slider 
	GAME_ENGINE->DrawBitmap(m_BmpSliderPtr, m_X, m_Y + OFFSET_Y_SLIDER);

	// draw lightbar 
	int xLightBar{ m_X + OFFSET_X_LIGHTBAR };
	GAME_ENGINE->DrawBitmap(m_BmpLightbarPtr, xLightBar, m_Y);

	// draw button 
	int xButton{ m_X + OFFSET_X_BUTTON };
	GAME_ENGINE->DrawBitmap(m_BmpButtonPtr, xButton, m_YButton);

	// paint on the lightbar to fill it according to sound volume
	GAME_ENGINE->SetColor(RGB(0, 247, 0));
	int xFill{ xLightBar + OFFSET_X_FILL };
	int yFill{ m_YButton + m_BmpButtonPtr->GetHeight() / 2 };
	GAME_ENGINE->FillRect(xFill, yFill, FILLWIDTH, bottomSlider - yFill + m_BmpButtonPtr->GetHeight() / 2);

	// redraw the lines of the lightbar that have been filled over
	GAME_ENGINE->SetColor(RGB(0, 99, 0));
	for (int count{}; m_Y + TOTALHEIGHT - count > m_YButton; ++count)
	{
		if (count % 7 < 2) GAME_ENGINE->DrawLine(xFill, bottomSlider - count + m_BmpButtonPtr->GetHeight() / 2, xFill + FILLWIDTH, bottomSlider - count + m_BmpButtonPtr->GetHeight() / 2);
	}
}

void Slider::ChangeVolume(int delta)
{
	int newValue{ m_Volume + delta };

	if (newValue >= 0 && newValue <= MAXVOLUME) 
	{
		m_Volume = newValue;
		UpdateButton();
		m_SoundChanged = true;
	}
}
	
void Slider::UpdateButton()
{
	m_YButton = m_Y + TOTALHEIGHT - SLIDERHEIGHT * m_Volume / MAXVOLUME;
}

void Slider::MouseMove(int x, int y)
{
	if (m_Clicked == true)
	{
		int bottomSlider{ m_Y + TOTALHEIGHT };
		m_YButton = min(max(y - m_DeltaYClick, bottomSlider - SLIDERHEIGHT), bottomSlider);
		m_Volume = (bottomSlider - m_YButton) * MAXVOLUME / SLIDERHEIGHT;
		m_SoundChanged = true;
	}
}

void Slider::MouseButtonAction(bool isLeft, bool isDown, int x, int y)
{
	if (isLeft == true && isDown == true)
	{
		int xButton{ m_X + OFFSET_X_BUTTON };

		if (x > xButton && x < xButton + m_BmpButtonPtr->GetWidth() && y > m_YButton && y < m_YButton + m_BmpButtonPtr->GetHeight())
		{
			m_DeltaYClick = y - m_YButton;
			m_Clicked = true;
		}
	}
	else if (isLeft == true && isDown == false)
	{
		m_Clicked = false;
	}
}
