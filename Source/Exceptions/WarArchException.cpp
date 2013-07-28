#include "WarArchException.hpp"

void WarArchException::SetErrorMessage(const std::string &errorMessage)
{
    humanReadableError = "WarArchException: ";
    humanReadableError.append(errorMessage);
}

std::string WarArchException::GetErrorMessage()
{
    return humanReadableError;
}