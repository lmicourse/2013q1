#include <functional>
#include <iostream>
#include <map>

class AB
{
public:
    AB(int a, int b): m_a(a), m_b(b) {}

    std::function<int()> f()
    {
        // return [m_a,m_b]() { return m_a + m_b; }; // compile error: m_a and m_b are not variables in this scope
        return [this]() { return m_a + m_b; }; // capture by value
    }

private:
    int m_a;
    int m_b;
};

void addLambda(std::map<std::string, std::function<int()>>& l)
{
    int s = 8;
    l["[s]"]  = [s]()     { return s; };
    l["[&s]"] = [&s]()    { return s; }; // crash or incorrect value, dangling reference
}

int apply(std::function<int()> f)
{
    return f();
}

int main()
{
    std::map<std::string, std::function<int()>> lambdas;
    int a = 0;
    int b = 2;
    lambdas["[=]"]      =    [=]()      { return a + b; };
    lambdas["[&]"]      =    [&]()      { return a + b; };
    lambdas["[a,b]"]    =    [a,b]()    { return a + b; };
    lambdas["[&a,b]"]   =    [&a,b]()   { return a + b; };
    lambdas["[a,&b]"]   =    [a,&b]()   { return a + b; };
    lambdas["[=,&b]"]   =    [=,&b]()   { return a + b; };
    lambdas["[&,b]"]    =    [&,b]()    { return a + b; };
    lambdas["AB.f()"]   =    AB(a,b).f();

    addLambda(lambdas);

    std::cout << "a=" << a << " b=" << b << " a+b=" << std::endl;

    for( auto l: lambdas)
    {
        std::cout << l.first << ": " << apply(l.second) << std::endl;
    }

    a = 1;
    b = 4;

    std::cout << std::endl;
    std::cout << "a=" << a << " b=" << b << " a+b=" << std::endl;

    for( auto l: lambdas)
    {
        std::cout << l.first << ": " << apply(l.second) << std::endl;
    }
}