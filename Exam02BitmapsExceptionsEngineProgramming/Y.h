#pragma once
#include <Windows.h>
#include <Gdiplus.h>


class Y
{

public:
    Gdiplus::Status imageToImage(IStream *pStreamIn, IStream *pStreamOut, BSTR wszOutputMimeType);
    Gdiplus::Status ConvertPNGToBMP(const wchar_t* pngPath, const wchar_t* bmpPath);
};
