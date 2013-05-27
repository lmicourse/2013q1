#include <stdio.h>

int main()
{
    int* nullPointer = NULL;
    int evenNumber=2;
    int neverUsed=evenNumber;
    bool wideScopeVariable;

    if (evenNumber%2 == 1)
    {
        wideScopeVariable = true;
        nullPointer = new int[evenNumber];
    }

    nullPointer[evenNumber-1]=evenNumber;

    delete nullPointer;

    return 0;
}
