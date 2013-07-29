#ifndef WarArchException_H
#define WarArchException_H

#include <exception>
#include <string>

//!The base exception class
/*!A base exception class for which all other Excetoions are based on
 * \pre NA
 * \post NA
 * \note */

class WarArchException : public virtual std::exception
{
    
public:
    
    //!Set the human readable message
    /*!Set a string with a message for the user/developer
     *  to see.
     * \pre NA
     * \post Sets message to string
     * \note NA*/
    void SetErrorMessage(const std::string &errorMessage);
    
    ~WarArchException() throw() {}
    virtual std::string GetErrorMessage();
protected:
    //Stored message for error throw
    std::string humanReadableError;
private:
    
};

#endif