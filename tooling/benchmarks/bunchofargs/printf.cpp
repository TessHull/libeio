#include <cstdio>
#include <string_view>
#include <fcntl.h>
#include <io.h>

void bunchofargs(int a, float b, std::string_view c)
{
    printf("With values a (%i), b (%f), and function c (%s), the result is %f\n", a, b, c.data(), (a*b));
}

int main()
{
    _setmode(_fileno(stdout), _O_BINARY);
    bunchofargs(2, 3.14, "Radians");
    return 0;
}