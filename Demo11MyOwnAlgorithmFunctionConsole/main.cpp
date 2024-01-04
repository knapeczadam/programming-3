#include <iostream>
#include <algorithm>

// DoubleNumber functor: class with overloaded ()-function, which doubles each value passed to it
template <typename ParamType>
class DoubleNumber 
{
public: 
	void operator()(ParamType& paramRef) 
	{
		paramRef *= 2;
	}
};

// my own Transform algorithm; it's a templated function, which calls CallableObject's function on every element in a range
template <typename PositionType, typename CallableObject>
void Transform(	PositionType positionPtr, 
				PositionType endPtr, 
				CallableObject callableObject) 
{
	while (positionPtr != endPtr) 
	{
		callableObject(*positionPtr);
		++positionPtr;
	}
}

// forward declarations for demo functions
void RunArrayDemo();
void RunVectorDemo();
void RunMapDemo();

// main demo program
int main()
{
	RunArrayDemo();
	//RunVectorDemo();
	//RunMapDemo();
}

//////////////////////////
// RunArrayDemo function
//////////////////////////

void RunArrayDemo()
{
	constexpr int SIZE{ 10 };

	////////////////////////////////
	// make an array of integers and fill it in
	////////////////////////////////
	int numbersArr[SIZE]{};
	for (int index{}; index < SIZE; ++index) 
		numbersArr[index] = index + 1;

	////////////////////////////////////
	// double the elements in the array 5 times; each time a different notation
	////////////////////////////////////
	// make temporary variables
	int* startPos = numbersArr;
	int* endPos = numbersArr + SIZE;
	DoubleNumber<int> doubleFunctor{};
	Transform(startPos, endPos, doubleFunctor);						// 1. pass temporary variables to the Transform function
	
	Transform(numbersArr, numbersArr + SIZE, DoubleNumber<int>{});	// 2. without temporaries, functor initialized with {} brackets
	Transform(numbersArr, numbersArr + SIZE, DoubleNumber<int>());	// 3. without temporaries, functor constructed with () brackets
	Transform(numbersArr, numbersArr + SIZE, [](int& element) {		// 4. with lambda, which does the same as the functor
		element *= 2;
	});	
	Transform(std::begin(numbersArr), std::end(numbersArr), DoubleNumber<int>{});	// 5. with std::begin() and std::end()

	/////////////////////
	// print the results
	/////////////////////
	for (int index{}; index < SIZE; ++index) 
		std::cout << numbersArr[index] << " ";
	
	std::cout << std::endl;
}

//////////////////////////
// RunVectorDemo function
//////////////////////////

#include <vector>
void RunVectorDemo()
{
	constexpr int SIZE{ 10 };

	////////////////////////////////
	// now we use the Transform function with an std::vector! :)
	// this works because the parameters are templated
	// first, make a vector of integers
	////////////////////////////////
	std::vector<int> numbersVec{};
	for (int index{}; index < SIZE; ++index) 
		numbersVec.push_back(index + 1);

	////////////////////////////////////
	// double the elements in the vector 5 times; each time a different notation
	////////////////////////////////////
	// make temporary variables
	std::vector<int>::iterator startPos = numbersVec.begin();
	std::vector<int>::iterator endPos	= numbersVec.end();
	DoubleNumber<int> doubleFunctor{};
	Transform(startPos, endPos, doubleFunctor);								// 1. pass temporary variables to the Transform function
	
	Transform(numbersVec.begin(), numbersVec.end(), DoubleNumber<int>{});	// 2. without temporaries, functor initialized with {} brackets
	Transform(numbersVec.begin(), numbersVec.end(), DoubleNumber<int>());	// 3. without temporaries, functor constructed with () brackets
	Transform(numbersVec.begin(), numbersVec.end(), [](int& element) {		// 4. with lambda, which does the same as the functor
		element *= 2;
	});
	Transform(std::begin(numbersVec), std::end(numbersVec), DoubleNumber<int>{});	// 5. with std::begin() and std::end()

	/////////////////////
	// print the results
	/////////////////////
	for (auto number : numbersVec) std::cout << number << " ";
	std::cout << std::endl;
}

//////////////////////////
// RunMapDemo function
//////////////////////////

// Adding a DoubleNumberMap functor: class with overloaded ()-function, which takes a KeyValue pair, and doubles the second element
template <typename Key, typename Value>
class DoubleNumberForMap
{
public:
	void operator()(std::pair<const Key, Value>& paramRef)
	{
		paramRef.second *= 2;
	}
};

#include <map>
void RunMapDemo()
{
	constexpr int SIZE{ 10 };

	////////////////////////////////
	// now we use the Transform function with an std::map
	// make an std::map<int, int>
	////////////////////////////////
	std::map<int, int> numbersMap{};
	for (int index{}; index < SIZE; ++index) 
		numbersMap.insert({ index + 1, index + 1});

	////////////////////////////////////
	// double the values in the map 5 times; each time a different notation
	////////////////////////////////////
	// make temporary variables
	std::map<int, int>::iterator startPos = numbersMap.begin();
	std::map<int, int>::iterator endPos	  = numbersMap.end();
	DoubleNumberForMap<int, int> doubleMapFunctor{};
	Transform(startPos, endPos, doubleMapFunctor);												// 1. pass temporary variables to the Transform function
	
	Transform(numbersMap.begin(), numbersMap.end(), DoubleNumberForMap<int, int>{});			// 2. without temporaries, functor initialized with {} brackets
	Transform(numbersMap.begin(), numbersMap.end(), DoubleNumberForMap<int, int>());			// 3. without temporaries, functor constructed with () brackets
	Transform(numbersMap.begin(), numbersMap.end(), [](std::pair<const int, int>& element) {	// 4. with lambda, which does the same as the functor
		element.second *= 2;
	});
	Transform(std::begin(numbersMap), std::end(numbersMap), DoubleNumberForMap<int, int>{});	// 5. with std::begin() and std::end()

	/////////////////////
	// print the results
	/////////////////////
	for (const auto& element: numbersMap) std::cout << element.second << " ";
	std::cout << std::endl;
}

