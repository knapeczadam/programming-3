// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <string>
#include <iostream>
#include <sstream>

#if defined(DEBUG) or defined(_DEBUG)
#define tstring std::wstring
#define tcout std::wcout
#define tcin std::wcin
#define tstringstream std::wstringstream
#else
#define tstring std::string
#define tcout std::cout
#define tcin std::cin
#define tstringstream std::stringstream
#endif
