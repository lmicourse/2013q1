#include <stdio.h>
#include <string.h>
#include <utility>

class X
{
public:
    X(const char* text)
    {
        copyText(text);
    }
    ~X()
    {
        delete m_text;
        m_text = nullptr;
    }

    char* getText() const
    {
        return m_text;
    }

    X& operator=(const X& other)
    {
        delete m_text;
        copyText(other.getText());
        return *this;
    }

    X& operator=(X&& other)
    {
        m_text = other.m_text;
        other.m_text = nullptr;
        return *this;
    }

private:
    void copyText(const char* text)
    {
        size_t length = strlen(text);
        if (length > 0)
        {
            m_text = new char[length+1];
            strncpy(m_text, text, length);
            m_text[length] = '\0';
        }
    }
private:
    char* m_text;
};

int f42()
{
    return 42;
}

int main()
{
    int variable1 = 43;
    // int&& rRef = variable1; //cannot bind lvalue to rvalue reference

    int&& rRef = variable1 + 1;
    ++rRef;
    printf("rRef = %d\n", rRef);

    rRef = f42();
    printf("rRef = %d\n", rRef);

    // int& lRef = f42(); //cannot bind temp value to reference
    // int& lRef = variable1 + 1; //cannot bind temp value to reference

    int& lRef  = variable1;
    printf("lRef = %d\n", lRef);

    int variable2 = 41;
    lRef = variable2; // this changes the value of variable1 !!!

    printf("lRef = %d\n", lRef);
    printf("variable1 = %d\n", variable1);
    printf("variable2 = %d\n", variable2);

    X x1("alma");
    X x2("barack");
    X x3("citrom");

    printf("\n");
    printf("x1 = '%s'\n", x1.getText());
    printf("x2 = '%s'\n", x2.getText());
    printf("x3 = '%s'\n", x3.getText());

    printf("\nx2 = x1\n");
    printf("----------\n");
    x2 = x1;

    printf("x1 = '%s'\n", x1.getText());
    printf("x2 = '%s'\n", x2.getText());
    printf("x3 = '%s'\n", x3.getText());

    printf("\nx1 = std::move(x3)\n");
    printf("x2 = X(\"dinnye\")\n");
    printf("----------\n");
    x1 = std::move(x3);
    x2 = X("dinnye");

    printf("x1 = '%s'\n", x1.getText());
    printf("x2 = '%s'\n", x2.getText());
    printf("x3 = '%s'\n", x3.getText());
}
