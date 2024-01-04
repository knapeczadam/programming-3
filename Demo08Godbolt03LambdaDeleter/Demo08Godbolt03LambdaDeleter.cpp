#include <fstream>
#include <iostream>
#include <memory>

// disable deprication warning for fopen
#pragma warning(disable : 4996)

int main() {
    std::ofstream("demo.txt") << 'x';  // prepare the file to read
    {
        using unique_file_t =
            std::unique_ptr<FILE, decltype([](FILE* fp) { fclose(fp); })>;
        unique_file_t fp(std::fopen("demo.txt", "r"));
        if (fp) std::cout << char(std::fgetc(fp.get())) << '\n';
    }  // `close_file()` called here (if `fp` is not null)
}