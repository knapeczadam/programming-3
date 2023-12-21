#include "framework.h"
#include "MyEngine.h"

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    MyEngine* myEnginePtr = new MyEngine(hInstance, nCmdShow, _T("MyEngine32"), 800, 600, false);
    const int result = myEnginePtr->Run();
    delete myEnginePtr;
    return result;
}