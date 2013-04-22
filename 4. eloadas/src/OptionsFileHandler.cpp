#include <unordered_map>
#include <string>

#include "IFile.h"
#include "Options.h"
#include "OptionsFileHandler.h"

OptionsFileHandler::OptionsFileHandler(IFile &file)
    : m_file(file)
{}

Options OptionsFileHandler::Read() const
{
    std::unordered_map<std::string, std::string> options;
    for(;;)
    {
        std::string line = m_file.ReadLine();
        if (line.empty())
        {
            break;
        }

        auto eqSignPos = line.find('=');

        if (eqSignPos != std::string::npos)
        {
            options[line.substr(0, eqSignPos)] = line.substr(eqSignPos + 1);
        }
    }

    return Options(options);
}

bool OptionsFileHandler::Write(const Options &options)
{
    if (options.GetOptions().empty())
    {
        return false;
    }

    for(auto option : options.GetOptions())
    {
        if ( ! m_file.WriteLine(option.first + "=" + option.second) )
        {
            return false;
        }
    }

    return true;
}
