#pragma once

#include "resource.h"
#include <windows.h>
#include <vector>

#include "MyEngine.h"

class MyApplication
{
public:
	// Constructor(s) and destructor
	MyApplication(MyEngine* enginePtr);				
	virtual ~MyApplication();						
												
	// Disabling default copy/move constructor and assignment operator
	MyApplication(const MyApplication& yRef)			= delete;
	MyApplication(MyApplication&& yRef)					= delete;
	MyApplication& operator=(const MyApplication& yRef)	= delete;
	MyApplication& operator=(MyApplication&& yRef)		= delete;

	//-------------------------------------------------
	// Own methods								
	//-------------------------------------------------
	void Activate(bool isActive);
	void LeftMouseButtonAction(int x, int y, bool isUp);
	void RightMouseButtonAction(int x, int y, bool isUp);
	void Paint();

private:
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	MyEngine* m_MyEnginePtr;

	std::vector<POINT> m_PointsVec{};
};