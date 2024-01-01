#pragma once

#include "resource.h"
#include <string>

class MyApplication;

class MyEngine
{
public:
	// Constructor(s) and destructor
	virtual ~MyEngine();		

	// Disabling default copy/move constructor and assignment operator.
	MyEngine(const MyEngine& yRef)				= delete;
	MyEngine(MyEngine&& yRef)					= delete;
	MyEngine& operator=(const MyEngine& yRef)	= delete;
	MyEngine& operator=(MyEngine&& yRef)		= delete;

	//-------------------------------------------------
	// Initialization						
	//-------------------------------------------------
	int Run(MyApplication* m_MyGamePtr);
	LRESULT HandleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static void Initialize(HINSTANCE hInstance, int nCmdShow);
	static MyEngine* GetSingleton();

	//-------------------------------------------------
	// API methods							
	//-------------------------------------------------
	void SetColor(COLORREF color);
	void FillEllipse(int x1, int y1, int radiusX, int radiusY);
	void DrawLine(int x1, int y1, int x2, int y2);
	void SetTitle(const std::wstring& text);

private:
	//-------------------------------------------------
	// Singleton implementation								
	//-------------------------------------------------
	MyEngine();
	static MyEngine* m_MyEnginePtr;

	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	std::wstring m_AppName, m_Title;

	HDC m_hDC;
	HWND m_hWnd;
	MyApplication* m_MyApplicationPtr{};

	static HINSTANCE m_Instance;
	static int m_Show;

	COLORREF m_Color{ RGB(255, 255, 255) };
};