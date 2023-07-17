#include <format>
#include <windows.h>
#include <fileapi.h>

int main()
{
    char str[128];
    std::format_to(str, "Hello World!\n");
    auto console{GetStdHandle(STD_OUTPUT_HANDLE)};
    (void)WriteFile(console, str, 13, nullptr, nullptr);
    return 0;
}