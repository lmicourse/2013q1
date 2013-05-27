#include <stdio.h>

int main()
{
    int* p = NULL;
    int a=2;

    if (a%2 == 1)
    {
        p = new int[a];
    }

    p[a-1]=a;

    delete p;

    return 0;
}
