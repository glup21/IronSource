#pragma once
#include <string>

class FileReaderService
{
private:
    FileReaderService() = delete;
public:
    static std::string ReadFile(std::string path);
};