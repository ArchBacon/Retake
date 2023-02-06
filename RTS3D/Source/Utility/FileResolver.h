#pragma once

#include <string>

class FileResolver
{
public:
    std::string static Resolve(const char* path);
};

#ifdef _PLATFORM_WINDOWS
inline std::string FileResolver::Resolve(const char* path)
{
    return path;
}
#endif

#ifdef _PLATFORM_RASPBERRY
inline std::string FileResolver::Resolve(const char* path)
{
    return "../../../" + std::string(path);
}
#endif
