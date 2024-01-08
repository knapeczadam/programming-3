#include "Y.h"

#include <Windows.h>
#include <Gdiplus.h>
#include <Shlwapi.h>
#include <Shlobj.h>
#include <comdef.h>

#pragma comment (lib,"Gdiplus.lib")
#pragma comment(lib, "Shlwapi.lib")

#include <objidl.h>
#include <gdiplus.h>

Gdiplus::Status Y::imageToImage(
  IStream *pStreamIn, IStream *pStreamOut, BSTR wszOutputMimeType)
{
    namespace G = Gdiplus;
    G::Status status = G::Ok;
    G::Image imageSrc(pStreamIn);
    status = imageSrc.GetLastStatus();
    if (G::Ok != status) {
      return status;
    }
    UINT numEncoders = 0;
    UINT sizeEncodersInBytes = 0;
    status = G::GetImageEncodersSize(&numEncoders, &sizeEncodersInBytes);
    if (status != G::Ok) {
      return status;
    }
    G::ImageCodecInfo *pImageCodecInfo = 
         (G::ImageCodecInfo *) malloc(sizeEncodersInBytes);
    status = G::GetImageEncoders(
          numEncoders, sizeEncodersInBytes, pImageCodecInfo);
    if (status != G::Ok) {
      return status;
    }
    CLSID clsidOut;
    status = G::UnknownImageFormat;
    for (UINT j = 0; j < numEncoders; j ++) {
      if (0 == wcscmp(pImageCodecInfo[j].MimeType, wszOutputMimeType)) {
        clsidOut = pImageCodecInfo[j].Clsid;
        status = G::Ok;
        break;
      }    
    }
    free(pImageCodecInfo);
    if (status != G::Ok) {
      return status;
    }
    return imageSrc.Save(pStreamOut, &clsidOut);
  }

// Function to convert a .png to a .bmp using GDI+
Gdiplus::Status Y::ConvertPNGToBMP(const wchar_t* pngPath, const wchar_t* bmpPath)
{
    using namespace Gdiplus;

    // Initialize GDI+
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Open the input .png file
    IStream* pStreamIn = NULL;
    HRESULT hr = SHCreateStreamOnFileW(pngPath, STGM_READ, &pStreamIn);
    if (FAILED(hr))
    {
        GdiplusShutdown(gdiplusToken);
        return Status::GenericError;
    }

    // Create the output .bmp file
    IStream* pStreamOut = NULL;
    hr = SHCreateStreamOnFileW(bmpPath, STGM_WRITE | STGM_CREATE, &pStreamOut);
    if (FAILED(hr))
    {
        pStreamIn->Release();
        GdiplusShutdown(gdiplusToken);
        return Status::GenericError;
    }

    // Convert .png to .bmp
    _bstr_t bstr(L"image/bmp");
    Status status = imageToImage(pStreamIn, pStreamOut, bstr);

    // Release resources
    pStreamIn->Release();
    pStreamOut->Release();

    // Shutdown GDI+
    GdiplusShutdown(gdiplusToken);

    return status;
}

// // WinMain function
// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
// {
//     // Example usage: convert "input.png" to "output.bmp"
//     const wchar_t* inputPNG = L"cat.png";
//     const wchar_t* outputBMP = L"cat.bmp";
//
//     Gdiplus::Status result = ConvertPNGToBMP(inputPNG, outputBMP);
//
//     // Handle the result (for demonstration purposes)
//     if (result == Gdiplus::Ok)
//     {
//         MessageBox(NULL, L"Conversion successful!", L"Success", MB_OK);
//         HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, outputBMP, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//         if (hBitmap)
//         {
//             DeleteObject(hBitmap);
//         }
//     }
//     else
//     {
//         MessageBox(NULL, L"Conversion failed!", L"Error", MB_OK | MB_ICONERROR);
//     }
//
//     return 0;
// }
