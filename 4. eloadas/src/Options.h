
#pragma once

#include <unordered_map>
#include <string>

class Options
{
public:
    explicit Options(const std::string& options);
    explicit Options(const std::unordered_map<std::string, std::string>& options);

    const std::unordered_map<std::string, std::string>& GetOptions() const;
    std::string GetOption(const std::string& key) const;

    Options& Add(const Options& other);

private:
    std::unordered_map<std::string, std::string> m_options;
};
