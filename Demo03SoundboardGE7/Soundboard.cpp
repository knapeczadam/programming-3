//-----------------------------------------------------------------
// Game File
// C++ Source - Soundboard.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Soundboard.h"									

//-----------------------------------------------------------------
// Soundboard methods																				
//-----------------------------------------------------------------

void Soundboard::Initialize(HINSTANCE hInstance)			
{
	// Set the required values
	AbstractGame::Initialize(hInstance);
	GAME_ENGINE->SetTitle(_T("Soundboard"));					
	GAME_ENGINE->RunGameLoop(true);		
	
	// Set the optional values
	GAME_ENGINE->SetWidth(640);
	GAME_ENGINE->SetHeight(480);
    GAME_ENGINE->SetFrameRate(50);
	//GAME_ENGINE->SetKeyList(String("QSDZ") + (TCHAR) VK_SPACE);
}

void Soundboard::Start()
{
	// load bitmaps
	m_BmpBgPtr				= new Bitmap(IDB_BG,		_T("BITMAP"));
	m_BmpSliderPtr			= new Bitmap(IDB_SLIDER,	_T("BITMAP"));
	m_BmpButtonPtr			= new Bitmap(IDB_BUTTON,	_T("BITMAP"));
	m_BmpLightbarPtr		= new Bitmap(IDB_LIGHTBAR,	_T("BITMAP"));

	// create font
	m_FontPtr				= new Font(_T("verdana"), true, true, false, 40);

	// load audio files
	m_Mp3MetropolisPtr		= new Audio(_T("Anne Clark - Sleeper In Metropolis.mp3"));
	m_Mp3RainPtr			= new Audio(_T("Samael-Rain.mp3"));
	m_Mp3FistPtr			= new Audio(_T("Tool - Stinkfist.mp3"));

	// make slider objects
	m_SliderMetropolisPtr	= new Slider(130, 140, m_BmpSliderPtr, m_BmpButtonPtr, m_BmpLightbarPtr, m_Mp3MetropolisPtr, STARTVOLUME_METROPOLIS);
	m_SliderRainPtr			= new Slider(280, 140, m_BmpSliderPtr, m_BmpButtonPtr, m_BmpLightbarPtr, m_Mp3RainPtr, STARTVOLUME_RAIN);
	m_SliderFistPtr			= new Slider(430, 140, m_BmpSliderPtr, m_BmpButtonPtr, m_BmpLightbarPtr, m_Mp3FistPtr, STARTVOLUME_FIST);

	// set audioloaded to true
	m_AudioLoaded			= true;
}

void Soundboard::End()
{
	delete m_BmpSliderPtr;
	delete m_BmpButtonPtr;
	delete m_BmpLightbarPtr;
	delete m_BmpBgPtr;

	delete m_FontPtr;

	delete m_Mp3RainPtr;
	delete m_Mp3MetropolisPtr;
	delete m_Mp3FistPtr;
	
	delete m_SliderMetropolisPtr;
	delete m_SliderRainPtr;
	delete m_SliderFistPtr;
}

void Soundboard::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
{	
	if (m_AudioLoaded == true)
	{
		m_SliderMetropolisPtr->MouseButtonAction(isLeft, isDown, x, y);
		m_SliderRainPtr->MouseButtonAction(isLeft, isDown, x, y);
		m_SliderFistPtr->MouseButtonAction(isLeft, isDown, x, y);
	}
}

void Soundboard::MouseMove(int x, int y, WPARAM wParam)
{	
	if (m_AudioLoaded == true)
	{
		m_SliderMetropolisPtr->MouseMove(x, y);
		m_SliderRainPtr->MouseMove(x, y);
		m_SliderFistPtr->MouseMove(x, y);
	}
}

void Soundboard::CheckKeyboard()
{	
	if (m_AudioLoaded == true)
	{
		if (GAME_ENGINE->IsKeyDown(_T('Q')))
		{
			m_SliderMetropolisPtr->ChangeVolume(2);
		}

		if (GAME_ENGINE->IsKeyDown(_T('A')))
		{
			m_SliderMetropolisPtr->ChangeVolume(-2);
		}

		if (GAME_ENGINE->IsKeyDown(_T('W')))
		{
			m_SliderRainPtr->ChangeVolume(2);
		}

		if (GAME_ENGINE->IsKeyDown(_T('S')))
		{
			m_SliderRainPtr->ChangeVolume(-2);
		}

		if (GAME_ENGINE->IsKeyDown(_T('E')))
		{
			m_SliderFistPtr->ChangeVolume(2);
		}

		if (GAME_ENGINE->IsKeyDown(_T('D')))
		{
			m_SliderFistPtr->ChangeVolume(-2);
		}
	}
}

void Soundboard::Tick()
{
	m_SliderMetropolisPtr->Tick();
	m_SliderRainPtr->Tick();
	m_SliderFistPtr->Tick();
}

void Soundboard::Paint(RECT rect)
{
	if (m_AudioLoaded == false)
	{
		GAME_ENGINE->DrawSolidBackground(RGB(90, 90, 82));

		GAME_ENGINE->SetFont(m_FontPtr);
		GAME_ENGINE->SetColor(RGB(0, 247, 0));
		GAME_ENGINE->DrawString(_T("Loading"), rect.right / 2 - 80, rect.bottom / 2 - 30);
	}
	else
	{		
		GAME_ENGINE->DrawBitmap(m_BmpBgPtr, 0, 0);

		m_SliderMetropolisPtr->Paint();
		m_SliderRainPtr->Paint();
		m_SliderFistPtr->Paint();
	}
}

void Soundboard::CallAction(Caller* callerPtr)
{
	// Insert the code that needs to be executed when a Caller has to perform an action
}



