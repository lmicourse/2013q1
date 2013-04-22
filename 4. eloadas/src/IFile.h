#pragma once

#include <string>

class IFile
{
public:
    virtual std::string ReadLine() const = 0;
    virtual bool WriteLine(const std::string& line) = 0;
};
