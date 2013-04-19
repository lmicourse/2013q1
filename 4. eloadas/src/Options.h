
#pragma once

#include <unordered_map>
#include <string>

class Options
{
public:
    Options(const std::string& options);
    //Options(const char* options);
    //Options(const char* options[]);

    const std::unordered_map<std::string, std::string>& GetOptions() const;
    std::string GetOption(const std::string& key) const;

private:
    std::unordered_map<std::string, std::string> m_options;
};
