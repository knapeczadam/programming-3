#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>

// helper function for the custom deleter demo below
void close_file(std::FILE* fp) { std::fclose(fp); }

int main() {
    std::ofstream("demo.txt") << 'x';  // prepare the file to read
    {
        // assert(close_file == &close_file);
        // static_assert(std::is_same<decltype(close_file),decltype(&close_file)>::value);
        using unique_file_t = std::unique_ptr<std::FILE, decltype(&close_file)>;
        unique_file_t fp(std::fopen("demo.txt", "r"), close_file);
        if (fp) std::cout << char(std::fgetc(fp.get())) << '\n';
    }  // `close_file()` called here (if `fp` is not null)
}