// BinaryReaderWriterConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <type_traits>

struct GameData
{
    char playerName[4]; // 4 bytes
    // std::string playerName; // ? bytes
    unsigned short score; // 2 bytes: 0 - 65535
};

class BinaryWriter
{
public:
    BinaryWriter(const std::string& filename)
    {
        // open file
        m_file.open(filename, std::ios::binary);
    }
    ~BinaryWriter()
    {
        // close file
        m_file.close();
    }
    
    void Write(const GameData& data)
    {
        // write data to file
        if (m_file.is_open())
        {
            // m_file.write((const char*) data.playerName.c_str(), data.playerName.size());
            // m_file.put(0xFF);
            m_file.write(data.playerName, sizeof(data.playerName));
            m_file.write(reinterpret_cast<const char*>(&data.score), sizeof(data.score));
        }
    }
private:
    // data members
    std::ofstream m_file;
};

class BinaryReader
{
public:
    BinaryReader(const std::string& filename)
    {
        // open file
        m_file.open(filename, std::ios::binary);
    }
    
    ~BinaryReader()
    {
        // close file
        m_file.close();
    }

    GameData Read()
    {
        // read data from file
        GameData data{};
        if (m_file.is_open())
        {
            // std::string playerName;
            // std::getline(m_file, playerName, static_cast<char>(0xFF));
            // data.playerName = playerName;
            m_file.read(data.playerName, sizeof(data.playerName));
            m_file.read(reinterpret_cast<char*>(&data.score), sizeof(data.score));
        }
        return data;
    }
private:
    // data members
    std::ifstream m_file;
};

int main()
{
    GameData data = { "BBE", 123 };

    // check if data is POD
    std::string pod = std::is_trivially_copyable<GameData>::value ? "true" : "false";
    std::cout << "Is POD: " << pod << std::endl;

    // write data to file
    // use scope to close file
    {
        BinaryWriter writer("data.bin");
        writer.Write(data);
    }

    // read data from file
    // use scope to close file
    {
        BinaryReader reader("data.bin");
        GameData data2 = reader.Read();
        std::cout << data2.playerName << ' ' << data2.score;
    }
}
