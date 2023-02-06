#pragma once

#include <string>

class FileResolver
{
public:
    std::string static Resolve(std::string path);
    std::string static Resolve(const char* path);
};
