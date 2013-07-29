#ifndef Archive_Header
#define Archive_H

/*!Main Archive Datastructure
 *  \brief Controls the file operation of a WAR archive
 *  \details Controls the file extraction and processing
 *      of a archive. Mostly in terms of extracting files
 *      to be processed by other tools
 *  \author    Bradley Clemetson
 *  \version   1.0.0
 *  \date      July 26, 2013
 *  \copyright LGPLv2
 */

#include "../Exceptions/WarArchiveException/WarArchiveException.hpp"

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
    //!Default WarArchive Constructor
    /*! Sets the default values to prepare for 
     *  loading the metadata of a archive
     * \pre NA
     * \post The inital data structs are set to default values
     * \note NA*/
    WarArchive();
    
    //!Default WarArchive Deconstructor
    /*! Deallocates memory used by WarArchive
     * \pre NA
     * \post Deletes the DataStructure
     * \note NA*/
    ~WarArchive();
    
    //!Loads the Archive MetaData
    /*! Loads the archive metadata in order to
     *  prepare for file extraction.
     * \pre filePath must goto a valid WAR Archive
     * \post Opens InputFile stream and loads metadata
     * \param [in] filepath The full file path to the WAR archive
     * \param [in] multiFile Does the archive contain more then one file
     * \note NA*/
    void LoadArchive(const std::string &filePath, bool multiFile = true);
    
    //!Extracts an entity from the archive to a file
    /*!Extact an entity from a file and save it to outFilePath
     * \pre Archive must be loaded
     * \post The resulting file is written to the outFilePath
     * \param [in] outFilePath The destination file path for the extracted
     *              entity.
     * \throws NoArchiveLoadedException EntityNumberOutofBoundsException
     * \note NA*/
    void ExtractEntity(const std::string &outFilePath, unsigned int entityNumber);
    
    //!Extracts an entity from the archive to a Vector
    /*!Extracts a file entity to a std::vector
     * \pre Archive must be loaded
     * \param [in] enetityNumber The desired entity to extract
     * \returns Pointer to a std::vector with entity
     * \throws NoArchiveLoadedException EntityNumberOutofBoundsException
     * \note The pointer taking the assignment must be empty, otherwise you got a leak*/
    std::vector<uint8_t> *ExtractEntity(unsigned int entityNumber);
    
    //!Closes the Archive
    /*! Closes the archive and cleans the data structure, allowing for a
     *  new archive to be loaded
     * \pre NA
     * \post Deallocates all internal datastructure variables
     * \note NA*/
     void CleanArchive();
    
    //!Returns the number of entities in an archive
    /*!Simple getter that returns the number of objects
     *  in an archive.
     * \pre Archive must be loaded
     * \returns The number of entities in an archive
     * \throws NoArchiveLoadedException
     * \note NA*/
    int GetNumberOfEntities();
    
    
protected:
    //!Closes the Archive ifstream
    /*!Closes the ifstream to the arhive, without
     *deallocating the datastructure
     * \pre Archive must be loaded
     * \post The ifstream is closed
     * \note NA*/
    void CloseArchive();
    
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