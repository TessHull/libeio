#include <cstdio>
#include <fcntl.h>
#include <io.h>

int main()
{
    _setmode(_fileno(stdout), _O_BINARY);
    printf("Hello World!\n");
    return 0;
}