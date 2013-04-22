#pragma once

class IFile;
class Options;

class OptionsFileHandler
{
public:
    explicit OptionsFileHandler(IFile& file);

    Options Read() const;
    bool Write(const Options& options);
private:
    IFile& m_file;
};
