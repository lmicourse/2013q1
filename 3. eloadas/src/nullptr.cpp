#include <stdio.h>

void f(int)
{
    printf("%s\n", "f(int)");
}

void f(char)
{
    printf("%s\n", "f(char)");
}

void f(const char*) // const - string literals are not writeable
{
    printf("%s\n", "f(char*)");
}

int main()
{
    printf(" f(0)       - "); f(0);

    printf(" f('0')     - "); f('0');

    printf(" f(\"0\")     - "); f("0");

    printf("!f(NULL)    - "); f(NULL);

    printf(" f(nullptr) - "); f(nullptr);
}
