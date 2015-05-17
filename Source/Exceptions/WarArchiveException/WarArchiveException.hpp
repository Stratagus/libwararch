#pragma once

#include "../WarArchException.hpp"
#include <exception>
#include <string>

class ArchiveException : public WarArchException {};
class InvalidEntityException : public ArchiveException {};
class NoArchiveLoadedException : public ArchiveException {};
class CorruptArchiveException : public ArchiveException {};
class EntityNumberOutofBoundsException : public ArchiveException
{
public:
    int badEntity;
};