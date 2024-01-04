
#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include <tchar.h>

#ifdef _UNICODE 
	#define tstring wstring
	#define tcout wcout
#else
	#define tstring string
	#define tcout cout
#endif

//-----------------------------------------------------
// MyStaticString Class									
//-----------------------------------------------------
class MyStaticString final
{
public:
	MyStaticString();				// Constructor
	~MyStaticString();				// Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	MyStaticString(const MyStaticString& other);
	MyStaticString& operator=(const MyStaticString& other);
	//MyStaticString(MyStaticString&& other) noexcept = delete;				// be careful: there's a difference between disabling and 'not writing' the move behaviour
	//MyStaticString& operator=(MyStaticString&& other) noexcept = delete;

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	void Add(TCHAR character);
	void Print() const;

private: 
	//-------------------------------------------------
	// Constants							
	//-------------------------------------------------
	static const int ARRAYSIZE{ 20 };

	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------


	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	TCHAR m_InternalData[ARRAYSIZE] {};
	int m_CurrentPos{};

	int m_ID;
	static int m_CountObjects;
};

 
