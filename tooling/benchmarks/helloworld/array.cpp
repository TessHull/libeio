#include <windows.h>
#include <fileapi.h>

int main()
{
    char str[]{"Hello World!\n"};
    auto console{GetStdHandle(STD_OUTPUT_HANDLE)};
    (void)WriteFile(console, str, sizeof(str)-1 , nullptr, nullptr);
    return 0;
}