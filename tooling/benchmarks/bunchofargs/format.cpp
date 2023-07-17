#include <format>
#include <string_view>
#include <windows.h>
#include <fileapi.h>

auto console{GetStdHandle(STD_OUTPUT_HANDLE)};

void bunchofargs(int a, float b, std::string_view c)
{
    auto str{std::format("With values a ({}), b ({:.6f}), and function c ({}), the result is {:.6f}\n", a, b, c, (a*b))};
    (void)WriteFile(console, str.c_str(), str.size(), nullptr, nullptr);
}

int main()
{
    bunchofargs(2, 3.14, "Radians");
    return 0;
}