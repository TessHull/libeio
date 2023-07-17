#include <iostream>
#include <iomanip>
#include <string_view>
#include <fcntl.h>
#include <io.h>

void bunchofargs(int a, float b, std::string_view c)
{
    std::cout << std::fixed << "With values a (" << a <<  "), b (" 
    << std::setprecision(6) << b << "), and function c (" << c << "), the result is " 
    << std::setprecision(6) << (a*b) << "\n";
}

int main()
{
    _setmode(_fileno(stdout), _O_BINARY);
    bunchofargs(2, 3.14, "Radians");
    return 0;
}