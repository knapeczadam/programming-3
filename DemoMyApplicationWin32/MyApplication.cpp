// MyApplication.cpp : Defines the entry point for the application.
//

#include "MyApplication.h"

MyApplication::MyApplication(MyEngine* enginePtr) : m_MyEnginePtr(enginePtr)
{
    m_MyEnginePtr->SetTitle(L"Lines");
}

MyApplication::~MyApplication()
{
	// nothing to destroy
}

//-------------------------------------------------
// Own methods								
//-------------------------------------------------
void MyApplication::LeftMouseButtonAction(int x, int y, bool isUp)
{
	if (isUp) m_PointsVec.push_back({ x, y });
}

void MyApplication::RightMouseButtonAction(int x, int y, bool isUp)
{
	if (isUp) m_PointsVec.clear();
}

void MyApplication::Paint()
{
    if (m_PointsVec.size() > 0)
    {
        m_MyEnginePtr->SetColor(RGB(255, 0, 0));

        m_MyEnginePtr->FillEllipse(m_PointsVec[0].x, m_PointsVec[0].y, 4, 4);

        for (int count = 1; count < (int)m_PointsVec.size(); ++count)
        {
            m_MyEnginePtr->DrawLine(m_PointsVec[count-1].x, m_PointsVec[count-1].y, m_PointsVec[count].x, m_PointsVec[count].y);
            m_MyEnginePtr->FillEllipse(m_PointsVec[count].x, m_PointsVec[count].y, 4, 4);
        }
    }
}

void MyApplication::Activate(bool isActive)
{
	if (isActive) 
        m_MyEnginePtr->SetTitle(L"Lines");
	else 
        m_MyEnginePtr->SetTitle(L"This window is inactive; go away.");
}