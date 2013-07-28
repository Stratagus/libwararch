#ifndef ArchiveException_Header
#define ArchiveException_Header

#include "../WarArchException.hpp"
#include <exception>
#include <string>

class ArchiveException : public WarArchException {};
class InvalidEntity : public ArchiveException {};
class EntityNumberOutofBounds : public ArchiveException
{
public:
    int badEntity;
};

#endif
