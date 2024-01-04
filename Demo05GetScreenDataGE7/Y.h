#pragma once

//-----------------------------------------------------
// Include Files
//-----------------------------------------------------


//-----------------------------------------------------
// Y Class									
//-----------------------------------------------------
class Y final
{
public:
	Y();				// Constructor
	~Y();				// Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	Y(const Y& other)					{}
	Y(Y&& other) noexcept				{}
	Y& operator=(const Y& other)		{}
	Y& operator=(Y&& other)	noexcept	{}

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------



private: 
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------


	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	
};

 