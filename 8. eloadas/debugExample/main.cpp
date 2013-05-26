#include <algorithm>
#include <iostream>

class SloppyVector
{
public:
    SloppyVector()
        : m_array(NULL)
    {}

    ~SloppyVector()
    {
        delete[] m_array;
    }

    size_t size() const
    {
        return sizeof m_array / sizeof m_array[0];
    }

    void push_back(int value)
    {
        size_t newIdx = size();

        increment();

        m_array[newIdx] = value;
    }

private:
    void increment()
    {
        if (m_array == NULL)
        {
            m_array = new int[1];
        }
        else
        {
            size_t arrayLength = size();
            int* newArray = new int[arrayLength+1];
            std::copy(m_array, m_array+arrayLength, newArray);
            m_array = newArray;
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const SloppyVector& vector);

private:

    int* m_array;
};

std::ostream& operator<<(std::ostream& os, const SloppyVector& vector)
{
    for (size_t i = 0 ; i < vector.size(); ++i)
    {
        os << vector.m_array[i];
    }
    return os;
}

int main()
{
    SloppyVector vector;

    vector.push_back(1);
    vector.push_back(3);
    vector.push_back(3);
    vector.push_back(7);

    std::cout << vector << std::endl;
}
