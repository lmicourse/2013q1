#include "Options.h"

Options::Options(const std::string& options)
{
    if (options.empty())
    {
        return;
    }


    std::string key("");
    std::string value("");
    std::string::size_type spacePos = 0;
    std::string::size_type wordPos  = 0;

    for(;;)
    {
        wordPos  = options.find_first_not_of(' ', spacePos);
        spacePos = options.find(' ', wordPos);
        if ( wordPos == std::string::npos)
        {
            if ( !key.empty() )
            {
                m_options[key] = "true";
            }
            break;
        }

        if (key.empty())
        {
            if (options.at(wordPos) != '-')
            {
                //Ignore incorrect part
                continue;
            }

            key = options.substr(wordPos + 1, spacePos - wordPos - 1);
        }
        else
        {
            value = options.substr(wordPos, spacePos - wordPos);
            if ( value.at(0) == '-' )
            {
                m_options[key] = "true";
                key = value.substr(1);
            }
            else
            {
                m_options[key] = value;
                key.clear();
                value.clear();
            }
        }
    }
}

Options::Options(const std::unordered_map<std::string, std::string> &options)
{
    m_options.insert(options.begin(), options.end());
}

const std::unordered_map<std::string, std::string>& Options::GetOptions() const
{
    return m_options;
}

std::string Options::GetOption(const std::string& key) const
{
    auto optionIt = m_options.find(key);
    if ( optionIt != m_options.end() )
    {
        return optionIt->second;
    }
    return "";
}

Options& Options::Add(const Options &other)
{
    for( auto item: other.GetOptions())
    {
        m_options[item.first] = item.second;
    }

    return *this;
}
