#include <vector>
#include <stdio.h>

class A
{
public:
    A()
        : m_a {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    {}
    A(int i)
        : m_a {1*i, 2*i, 3*i, 4*i, 5*i, 6*i, 7*i, 8*i, 9*i, 10*i }
    {}

    int* begin()
    {
        return m_a;
    }

    int* end()
    {
        return m_a+10;
    }

private:
    int m_a[10];
};

int main()
{
    int a[] = {1, 2, 3, 4, 5};

    for (int& i : a)
    {
        printf("%d, ", i++);
    }
    printf("\n");

    for (auto i : a)
    {
        printf("%d, ", i);
    }
    printf("\n");

// --------------------
    std::vector<int> v {5, 4, 3, 2, 1};

    for (auto& i : v)
    {
        printf("%d, ", i--);
    }
    printf("\n");

    for (int i : v)
    {
        printf("%d, ", i);
    }
    printf("\n");

// --------------------
    for (auto i : {2, 4, 6, 8, 10})
    {
        printf("%d, ", i);
    }
    printf("\n");
// --------------------

    for (auto i : A(5))
    {
        printf("%d, ", i);
    }
    printf("\n");
}
