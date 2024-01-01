// MyApplication.cpp : Defines the entry point for the application.
//

#include "MyApplication.h"

#include "MyEngine.h"
#define MY_ENGINE MyEngine::GetSingleton()

MyApplication::MyApplication()
{
    MY_ENGINE->SetTitle(L"Lines");
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
        MY_ENGINE->SetColor(RGB(255, 0, 0));

        MY_ENGINE->FillEllipse(m_PointsVec[0].x, m_PointsVec[0].y, 4, 4);

        for (int count = 1; count < (int)m_PointsVec.size(); ++count)
        {
            MY_ENGINE->DrawLine(m_PointsVec[count-1].x, m_PointsVec[count-1].y, m_PointsVec[count].x, m_PointsVec[count].y);
            MY_ENGINE->FillEllipse(m_PointsVec[count].x, m_PointsVec[count].y, 4, 4);
        }
    }
}

void MyApplication::Activate(bool isActive)
{
	if (isActive) 
        MY_ENGINE->SetTitle(L"Lines");
	else 
        MY_ENGINE->SetTitle(L"This window is inactive; go away.");
}