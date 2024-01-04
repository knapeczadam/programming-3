// DemoSentenceIteratorConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using Sentence = std::vector<std::string>;
using SentenceIterator = Sentence::iterator;


int main()
{
	Sentence sentence = { "Hello", "World", "!" };
	for (SentenceIterator it = sentence.begin(); it != sentence.end(); ++it)
	{
				std::cout << *it << std::endl;
	}
}
