#include <fstream>
#include <iostream>
#include <filesystem>
#include <cassert>
#include <string>
#include <type_traits>

#ifdef _MSVC_LANG
static_assert(_MSVC_LANG >= 201703L, "This program requires at least C++17");
#else
static_assert(__cplusplus >= 201703L, "This program requires at least C++17");
#endif

using std::cout, std::endl;

struct Float3f {
	float x, y, z;
};

void example1() {
	// std::string pod = std::is_pod<Float3f>() == 1 ? "yes" : "no";
	std::string pod = std::is_trivially_copyable<Float3f>() == 1 ? "yes" : "no";
	std::cout << "Is a Float3 struct a pod: " << pod << std::endl;

	// pod = std::is_pod<std::string>() == 1 ? "yes" : "no";
	pod = std::is_trivially_copyable<std::string>() == 1 ? "yes" : "no";
	std::cout << "Is a std::string a pod: " << pod << std::endl;

	Float3f toWrite;
	toWrite.x = 5.2f;
	toWrite.y = 5.1f;
	toWrite.z = 9.1f;

	if (std::ofstream temp{ "test.bin", std::ios::binary };  temp.is_open()) {
		// temp << toWrite.x << toWrite.y << toWrite.z;
		temp.write(reinterpret_cast<const char*>(&toWrite), sizeof(toWrite));
		temp.close();
	}
	else
	{
		cout << "file failed to open!" << endl;
	}


	Float3f toRead{};

	if (std::ifstream input{ "test.bin", std::ios::binary }; input.is_open()) {
		input.read((char*)&toRead, sizeof(toRead));
		assert(toRead.x == toWrite.x);
		assert(toRead.y == toWrite.y);
		assert(toRead.z == toWrite.z);
		input.close();
	}

	std::cout << "original float3 : [" << toWrite.x << ", " << toWrite.y << ", " << toWrite.z << "]" << std::endl;
	std::cout << "read float3 : [" << toRead.x << ", " << toRead.y << ", " << toRead.z << "]" << std::endl;
}

void example2()
{
	std::ifstream myfile{ "test.bin", std::ios::binary };
	std::streampos begin = myfile.tellg();
	myfile.seekg(0, std::ios::end);
	std::streampos end = myfile.tellg();
	myfile.close();
	std::cout << "size is: " << (end - begin) << " bytes." << std::endl;
}

void example2b()
{
	std::filesystem::path myFilePath{ "test.bin" };
	cout << "the size is: " << std::filesystem::file_size("test.bin") << endl;
	cout << std::filesystem::absolute(myFilePath) << endl;
}


void example3()
{
	const std::filesystem::path sandbox{ "sandboxDirectory" };
	std::filesystem::create_directories(sandbox / "dir1" / "dir2");
	std::ofstream{ sandbox / "file1.txt" };
	std::ofstream{ sandbox / "file2.txt" };

	std::filesystem::rename(sandbox / "file1.txt", sandbox / "fileA.txt");

	std::cout << "directory_iterator:\n";
	for (auto const& dir_entry : std::filesystem::directory_iterator{ sandbox })
		std::cout << dir_entry << '\n';

	std::cout << "recursive_directory_iterator:\n";
	for (auto const& dir_entry : std::filesystem::recursive_directory_iterator{ sandbox })
		std::cout << dir_entry << '\n';

	std::filesystem::remove_all(sandbox);
}


struct TeleportLocation
{
	bool isActive;
	uint8_t value;     //uncomment for #3
	// bool isVisible;	 //uncomment for #2
	// uint16_t strength; //uncomment for #2
	float x, y, z;
};

void example4()
{
	// TeleportLocation spawnPoint{ true, 1, 2, 3 };
	// TeleportLocation spawnPoint{ true, true, 0xADDE, 0.f, 0.f, 0.f }; //#2
	TeleportLocation spawnPoint{ true, 0xEE, 0.f, 0.f, 0.f };        // #3
	cout << "size of bool: " << sizeof(bool) << endl;
	cout << "size of float: " << sizeof(float) << endl;
	cout << "expected size of TeleportLocation: " << sizeof(bool) + 3 * sizeof(float) << endl;
	cout << "size of TeleportLocation: " << sizeof(TeleportLocation) << endl;

	if (std::ofstream myOutput{ "myFile.bin", std::ios::binary }; myOutput.is_open()) {
		myOutput.write((const char*)&spawnPoint, sizeof(spawnPoint));
		myOutput.close();
		cout << std::filesystem::file_size("myFile.bin") << endl;
	}
	else
	{
		cout << "could not open file!" << endl;
	}
}

struct NPC
{
	std::string name;
	float x, y, z;
};

void example5()
{
	NPC skeleton{ "Benedict the third, destroyer of worlds", 1, 2, 3 };

	if (std::ofstream myOutput{ "myFile2.bin", std::ios::binary }; myOutput.is_open()) {
		myOutput.write((const char*)skeleton.name.c_str(), skeleton.name.size());
		myOutput.put(0xFF);
		myOutput.write((const char*)&skeleton.x, sizeof(float) * 3);
		//myOutput.write((const char*)&skeleton, sizeof(skeleton));
		myOutput.close();
		cout << "The size of myfile2 is " << std::filesystem::file_size("myFile2.bin") << endl;
	}
	else
	{
		cout << "Dont be as stupid as me" << endl;
	}

	;
	if (std::ifstream input{ "myFile2.bin", std::ios::binary }; input.is_open())
	{
		//input.read((char*)&myName, 8);  //always reads 8 characters 

		//char myName[256]{};				//filling the buffer with 0s to guarantee a zero terminated string
		//input.getline(myName, 255, 0xFF); //needs a buffer

		std::string myName;
		std::getline(input, myName, static_cast<char>(0xFF));
		Float3f location{};
		input.read((char*)&location, sizeof(location));

		input.close();
		cout << myName << endl;
		cout << location.x << ", " << location.y << ", " << location.z << endl;
	}
	else
	{
		cout << "Dont be as stupid as me" << endl;
	}

}

void example6()
{
	NPC skeleton{ "Benedict!!123456", 1, 2, 3 };

	if (std::ofstream myOutput{ "myFile3.bin", std::ios::binary }; myOutput.is_open()) {
		//myOutput.write((const char*)&skeleton, sizeof(skeleton));  //does not work correctly
		myOutput.put(static_cast<char>(skeleton.name.size()));
		myOutput.write((const char*)skeleton.name.c_str(), skeleton.name.size());
		//myOutput.write((const char*)&skeleton.x, sizeof(float)); //to much typing
		//myOutput.write((const char*)&skeleton.y, sizeof(float));
		//myOutput.write((const char*)&skeleton.z, sizeof(float));
		myOutput.write((const char*)&skeleton.x, sizeof(float) * 3);

		myOutput.close();
		cout << "The size of myfile2 is " << std::filesystem::file_size("myFile3.bin") << endl;
	}
	else
	{
		cout << "Dont be as stupid as me" << endl;
	}

	if (std::ifstream input{ "myFile3.bin", std::ios::binary }; input.is_open())
	{
		char myName[255];
		Float3f location{};
		char stringSize{};
		//input.read(&stringSize, 1);
		stringSize = input.get();		//the other side of put()
		input.read(myName, stringSize);
		myName[stringSize] = 0;			//add a terminator
		input.read((char*)&location, sizeof(float) * 3);
		input.close();
		cout << myName << endl;
		cout << location.x << ", " << location.y << ", " << location.z << endl;
	}
	else
	{
		cout << "Dont be as stupid as me" << endl;
	}
}

int main() {
	// example1();
	// example2();
	// example2b();
	// example3();
	// example4();
	// example5();
	example6();
}