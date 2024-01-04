
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
// MySimpleString Class									
//-----------------------------------------------------
class MySimpleString final
{
public:
	MySimpleString();				// Constructor
	~MySimpleString();				// Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	MySimpleString(const MySimpleString& other);
	MySimpleString(MySimpleString&& other) noexcept;
	MySimpleString& operator=(const MySimpleString& other);
	MySimpleString& operator=(MySimpleString&& other) noexcept;

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
	TCHAR* m_InternalDataPtr{};
	int m_CurrentPos{};

	int m_ID;
	static int m_CountObjects;
};

 
