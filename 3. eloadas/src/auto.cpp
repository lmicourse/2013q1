#include <vector>
#include <iostream>

class A
{
public:
    A() : m_a(0) {}
//    A(auto i) : m_a(i) {} // compiler error
    int getA() { return m_a; }
private:
   // auto m_a = 1; // compile error!
    int m_a;
};

void f(int)
{
    printf("%s\n", "f(int)");
}

// void f(auto) compiler error
// {
//     printf("%s\n", "f(auto)");
// }

void g(int)
{
    printf("%s\n", "g(int)");
}

void g(double)
{
    printf("%s\n", "g(double)");
}

// auto returnAuto() // compile error
// {
//     return 1;
// }

auto returnAutoDouble() -> double // trailing return
{
    return 1;
};

auto returnAutoInt() -> int // trailing return
{
    return 1;
};


int main()
{
    auto i = 3;
    auto d = 3.14;
    const auto& cRefD = d;
    // ++cRefD; // compile error;

    printf("f(i) - "); f(i);
    printf("f(d) - "); f(d);
    printf("g(i) - "); g(i);
    printf("g(d) - "); g(d);

    printf("g(cRefD) - "); g(cRefD);

    printf("g(returnAutoInt())    - "); g(returnAutoInt());
    printf("g(returnAutoDouble()) - "); g(returnAutoDouble());

    // std::vector<auto> v {1, 2, 3, 4, 5}; // compile error
    std::vector<int> v {1, 2, 3, 4, 5};

    for (auto iter = v.begin(); iter != v.end(); ++iter)
    {
        printf("%d, ", *iter);
    }
    printf("\n");
}
