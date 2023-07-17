#include <format>
#include <string_view>
#include <windows.h>
#include <fileapi.h>

int main()
{
    auto str{std::vformat("Hello World!\n", std::format_args())};
    auto console{GetStdHandle(STD_OUTPUT_HANDLE)};
    (void)WriteFile(console, str.c_str(), str.size(), nullptr, nullptr);
    return 0;
}