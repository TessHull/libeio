#include <string_view>
#include <string>
#include <windows.h>
#include <fileapi.h>

auto console{GetStdHandle(STD_OUTPUT_HANDLE)};

void bunchofargs(int a, float b, std::string_view c)
{
    std::string str{"With values a ("};
    str += std::to_string(a) + "), b (" + std::to_string(b) + "), and function c (" + c.data() + "), the result is " + std::to_string(a*b) + "\n";
    (void)WriteFile(console, str.c_str(), str.size(), nullptr, nullptr);
}

int main()
{
    bunchofargs(2, 3.14, "Radians");
    return 0;
}