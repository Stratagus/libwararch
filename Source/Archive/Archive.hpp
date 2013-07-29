#ifndef Archive_Header
#define Archive_H

/*!WarArchive Datastructure
 *  \brief    
 *  \details   
 *  \author    Bradley Clemetson
 *  \version   1.0.0
 *  \date      July 8, 2013
 *  \copyright LGPLv2
 */

#include "../Exceptions/ArchiveException/ArchiveException.hpp"

#include <fstream>
#include <string>
#include <vector>


//Allow Windows to use 8/16/32 byte values
#if defined(_WIN32)
    #include <stdint.h>
    typedef uint8_t u_int8_t;
    typedef uint16_t u_int16_t;
    typedef uint32_t u_int32_t;
#else
    #include <inttypes.h>
#endif

class WarArchive
{
public:
    WarArchive();
    ~WarArchive();
    void LoadArchive(const std::string &filePath);
    void ExtractEntity(const std::string &outFilePath, unsigned int entityNumber);
    std::vector<uint8_t> *ExtractEntity(unsigned int entityNumber);
    void CloseArchive();
    int GetNumberOfEntities();
    
    
protected:
    void CleanArchive();
    
    //The filestream open to the archive itself
    std::ifstream *currentArchiveFileStream;
    
    //How far over the archive should we skip before reading
    //(in bytes)
    std::vector<uint32_t> *fileOffsets;
    
    //War archive header information
    uint16_t numberOfEntities;
    uint32_t magicNumber;
    uint16_t type;
private:
    
};

#endif