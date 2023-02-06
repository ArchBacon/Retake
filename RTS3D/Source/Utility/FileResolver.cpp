#include "FileResolver.h"

inline std::string FileResolver::Resolve(std::string path)
{
#ifdef _PLATFORM_RASPBERRY
    return "../../../" + path;
#endif
    
    return path;
}

std::string FileResolver::Resolve(const char* path)
{
    return Resolve(std::string(path));
}
