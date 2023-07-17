#include <iostream>
#include <fcntl.h>
#include <io.h>

int main()
{
    _setmode(_fileno(stdout), _O_BINARY);
    std::cout << "Hello World!" << std::endl;
    return 0;
}
