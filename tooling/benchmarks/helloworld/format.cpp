#include <format>
#include <windows.h>
#include <fileapi.h>

int main()
{
    auto str{std::format("Hello World!\n")};
    auto console{GetStdHandle(STD_OUTPUT_HANDLE)};
    (void)WriteFile(console, str.c_str(), str.size(), nullptr, nullptr);
    return 0;
}