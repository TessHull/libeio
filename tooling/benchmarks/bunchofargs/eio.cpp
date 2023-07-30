#include <eio/eio>

void bunchofargs(int a, float b, std::string_view c)
{
    eio::out.ref(a).ref(b);
    eio::out.ref(c).val(a*b).print("With values a ({}), b ({:.6f}), and function c ({}), the result is {:.6f}\n");
}

int main()
{
    bunchofargs(2, 3.14, "Radians");
    return 0;
}