#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <regex>
#include <optional>
#include <filesystem>

//-----------------------------------------------------------------
// StudentScoreIn
//-----------------------------------------------------------------
struct StudentScoreIn
{
    std::string lastName;
    std::string firstName;
    int         score;
};

//-----------------------------------------------------------------
// StudentScoreOut
//-----------------------------------------------------------------
struct StudentScoreOut
{
    std::string lastName;
    std::string firstName;
    char        score;
};

bool IsInteger(const std::string& str, int& number)
{
    try
    {
        size_t pos{};
        number = std::stoi(str, &pos);
        return pos == str.length();
        // // If pos is equal to the length of the string, then the entire string was consumed
    }
    catch (std::invalid_argument&)
    {
        return false; // Conversion to integer failed
    }
    catch (std::out_of_range&)
    {
        return false; // Value is out of the range for an integer
    }
}

bool IsFloatingPoint(const std::string& str, float& number)
{
    try
    {
        size_t pos{};
        number = std::stof(str, &pos);
        // string should contain a '.' character
        if (str.find('.') == std::string::npos)
        {
            return false;
        }
        return pos == str.length();
        // // If pos is equal to the length of the string, then the entire string was consumed
    }
    catch (std::invalid_argument&)
    {
        return false; // Conversion to float failed
    }
    catch (std::out_of_range&)
    {
        return false; // Value is out of the range for a float
    }
}

std::pair<bool, std::pair<std::optional<int>, std::optional<float>>> IsNumber(const std::string& str)
{
    if (std::regex_match(str, std::regex{"(([\\+\\-]*\\d*\\.*\\d+[eE])?([\\+\\-]*\\d*\\.*\\d+))"}))
    {
        // integer
        int number1;
        if (IsInteger(str, number1))
        {
            return {true, {number1, std::nullopt}};
        }
        
        // floating point
        float number2;
        if (IsFloatingPoint(str, number2))
        {
            return {true, {std::nullopt, number2}};
        }
    }
    return {false, {std::nullopt, std::nullopt}};
}

bool IsValidStudentScore(const std::string& in, StudentScoreIn& studentScore)
{
    if (std::ranges::count(in, ',') != 2) return false;
    if (std::ranges::count(in, ' ') != 0) return false;
    
    std::stringstream ss(in);
    std::vector<std::string> result;
    
    while (ss.good())
    {
        std::string substr;
        std::getline(ss, substr, ',');
        result.push_back(substr);
    }
    
    const std::string lastName  = result[0];
    const std::string firstName = result[1];
    const std::string scoreStr  = result[2];
    
    int score;
    if (not IsInteger(scoreStr, score)) return false;
    
    studentScore = {lastName, firstName, score};

    return true;
}

bool compareStudents(const StudentScoreIn& student1, const StudentScoreIn& student2)
{
    // Compare by score in increasing order
    if (student1.score < student2.score)
    {
        return true;
    }
    else if (student1.score > student2.score)
    {
        return false;
    }

    // If scores are equal, compare alphabetically by last name, then first name
    if (student1.lastName != student2.lastName)
    {
        return student1.lastName < student2.lastName;
    }

    return student1.firstName < student2.firstName;
}

int main()
{
    //--------------------------------------------------
    // Read scores.csv
    //--------------------------------------------------
    std::ifstream inputFile("scores.csv");
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open scores.csv\n";
        return 1;
    }

    std::vector<StudentScoreIn> studentScoresIn;

    std::string line;
    int lineCount = 0;
    while (std::getline(inputFile, line))
    {
        // skip first line
        if (lineCount++ == 0)
            continue;
        
        StudentScoreIn studentScore;
        
        if (IsValidStudentScore(line, studentScore))
        {
            studentScoresIn.push_back(studentScore);
        }
        else
        {
            std::cerr << "Invalid line: " << line << '\n';
        }
    }

    //--------------------------------------------------
    // Sort the students
    //--------------------------------------------------
    std::ranges::sort(studentScoresIn, compareStudents);

    //--------------------------------------------------
    // Partition the students
    //--------------------------------------------------
    std::ranges::stable_partition(studentScoresIn, [](const StudentScoreIn& student)
    {
        return student.score >= 10;
    });

    //--------------------------------------------------
    // Copy StudentScoresIn to StudentScoresOut
    //--------------------------------------------------
    std::vector<StudentScoreOut> studentScoresOut;
    for (const auto& student : studentScoresIn)
    {
        StudentScoreOut studentScoreOut;
        studentScoreOut.lastName  = student.lastName;
        studentScoreOut.firstName = student.firstName;
        studentScoreOut.score     = static_cast<char>(student.score);
        studentScoresOut.push_back(studentScoreOut);
    }

    //--------------------------------------------------
    // Save to ordered_scores.csv
    //--------------------------------------------------
    std::ofstream outputFileCSV("ordered_scores.csv");
    if (!outputFileCSV.is_open())
    {
        std::cerr << "Error: Unable to open ordered_scores.csv for writing\n";
        return 1;
    }

    // Write header
    outputFileCSV << "LastName,FirstName,Score\n";
    
    for (const auto& student : studentScoresIn)
    {
        outputFileCSV << student.lastName << ',' << student.firstName << ',' << student.score << '\n';
    }

    //--------------------------------------------------
    // Save to ordered_scores.bin
    //--------------------------------------------------
    std::ofstream outputFileBin("ordered_scores.bin", std::ios::binary);
    if (!outputFileBin.is_open())
    {
        std::cerr << "Error: Unable to open ordered_scores.bin for writing\n";
        return 1;
    }

    for (const auto& student : studentScoresOut)
    {
        outputFileBin.put(student.lastName.size());
        outputFileBin.write(reinterpret_cast<const char*>(student.lastName.c_str()), student.lastName.size());
        outputFileBin.put(student.firstName.size());
        outputFileBin.write(reinterpret_cast<const char*>(student.firstName.c_str()), student.firstName.size());
        outputFileBin.write(reinterpret_cast<const char*>(&student.score), sizeof(student.score));
    }

    //--------------------------------------------------
    // close files
    //--------------------------------------------------
    inputFile.close();
    outputFileCSV.close();
    outputFileBin.close();

    //--------------------------------------------------
    // check file sizes
    //--------------------------------------------------
    std::filesystem::path orderedCSV{"ordered_scores.csv"};
    std::filesystem::path orderedBin{"ordered_scores.bin"};
    
    auto orderedCSVSize = std::filesystem::file_size(orderedCSV);
    auto orderedBinSize = std::filesystem::file_size(orderedBin);
    
    if (orderedCSVSize > orderedBinSize)
    {
        std::cout << "ordered_scores.csv is larger than ordered_scores.bin\n";
    }
    else if (orderedCSVSize < orderedBinSize)
    {
        std::cout << "ordered_scores.bin is larger than ordered_scores.csv\n";
    }
    else
    {
        std::cout << "ordered_scores.csv and ordered_scores.bin are the same size\n";
    }

    std::cout << "Files created successfully.\n";

    return 0;
}
