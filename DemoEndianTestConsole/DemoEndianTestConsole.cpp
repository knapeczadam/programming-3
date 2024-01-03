#include <iostream>

int main()
{
    union
    {
        float number{};                             //4 bytes
        unsigned char bytes[sizeof(number)];        //the same 4 bytes
    } u1, u2;
    std::cout << "size of u1 = " << sizeof(u1) <<std::endl; 
    u1.bytes[0] = 0x66;
    u1.bytes[1] = 0x66;
    u1.bytes[2] = 0xA6;
    u1.bytes[3] = 0x40;
    std::cout << "The float value of u1 is : " << u1.number << std::endl;
    u2.bytes[0] = 0x40;
    u2.bytes[1] = 0xA6;
    u2.bytes[2] = 0x66;
    u2.bytes[3] = 0x66;
    std::cout << "The float value of u2 is : " << u2.number << std::endl;
    getchar();
    return 0;
}
