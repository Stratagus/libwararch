#include "Archive.hpp"
#include <iostream>

WarArchive::WarArchive()
{
    currentArchiveFileStream = NULL;
}

WarArchive::~WarArchive()
{

}
void WarArchive::LoadArchive(const std::string &filePath)
{
    CleanArchive();
    
    currentArchiveFileStream = new std::ifstream;
    
    currentArchiveFileStream->open(filePath.c_str(), std::ios::binary);
    currentArchiveFileStream->exceptions(std::ifstream::badbit | std::ifstream::failbit | std::ifstream::eofbit);
    
    //Read in the magic number
    currentArchiveFileStream->read((char *) &magicNumber, 4);
    //Read in the number of entities (files) in the archive
    currentArchiveFileStream->read((char *) &numberOfEntities, 2);
    //Read in the types
    currentArchiveFileStream->read((char *) &type, 2);
    
    if(!fileOffsets)
    {
        fileOffsets = new std::vector<uint32_t>;
    }
    fileOffsets->resize(numberOfEntities);

    //Populate the fileOffsets table
    for(int currentGetFileOffset = 0; currentGetFileOffset < numberOfEntities; currentGetFileOffset++)
    {
        currentArchiveFileStream->read((char *) &fileOffsets->at(currentGetFileOffset), 4);
    }
    
}

void WarArchive::LoadArchive(std::vector<char> *loadedFile)
{
    /*CleanArchive();
    std::vector<char>::iterator currentDataPosition = loadedFile->begin();
    
    std::copy(currentDataPosition, (currentDataPosition += 4), &magicNumber);
    std::copy(currentDataPosition, (currentDataPosition += 2), &numberOfEntities);
    std::copy(currentDataPosition, (currentDataPosition += 2), &type);
    
    fileOffsets->resize(numberOfEntities);
    
    for(int currentOffsetLoad = 0; currentOffsetLoad < numberOfEntities; currentOffsetLoad++)
    {
        std::copy(currentDataPosition, (currentDataPosition +=4), fileOffsets->at(currentOffsetLoad));
    }*/
    
    //war->op[i] = war->data + war->filesize;
}

std::vector<uint8_t> *WarArchive::ExtractEntity(unsigned int entityNumber)
{
    if (!currentArchiveFileStream)
    {
        NoArchiveLoadedException noArchive;
        noArchive.SetErrorMessage("No archive has been loaded");
        throw noArchive;
    }
    if(entityNumber > numberOfEntities)
    {
        EntityNumberOutofBoundsException outOfBounds;
        outOfBounds.SetErrorMessage("Entity extraction value out of bounds");
        outOfBounds.badEntity = entityNumber;
    }
    
    //Seek to the correct file offset to begin reading
    currentArchiveFileStream->seekg(fileOffsets->at(entityNumber));
    
    //Get the Uncompressed file length data and compression flag data
    uint32_t unCompressedFileLength;
    currentArchiveFileStream->read((char *) &unCompressedFileLength, 4);
    
    //Get the top eight bits to find out the compression flags (Find if the file is compressed
    uint8_t compressionFlags;
    compressionFlags = (unCompressedFileLength >> 24);
    
    //Mask for the actual uncompressed file size
    unCompressedFileLength &= 0x00FFFFFF;
    
    //Create the vector to hold the resulting data
    std::vector<uint8_t> *unCompressedFile = new std::vector<uint8_t>(unCompressedFileLength);
    
    //If the data is compressed
    if(compressionFlags == 0x20)
    {
        //Create a vector iterator to hold where data is to be written to
        //std::vector<uint8_t>::iterator unCompressedFilePosition(unCompressedFile->begin());
        
        //Create the lookup table for LZSS
        std::vector<uint8_t> lookAheadBuffer(4096);
        //std::vector<uint8_t>::iterator lookAheadBufferPosition(lookAheadBuffer.begin());
        
        //Current position in the lookAheadTables
        int byteIndex = 0;
        unsigned int currentWritePosition = 0;
        
        for(int currentProcessingByte = 0; currentProcessingByte < unCompressedFileLength; currentProcessingByte++)
        {
            //The type of data in a specific byte
            uint8_t byteFlags;
            currentArchiveFileStream->read((char *) &byteFlags, 1);
            
            for(int currentProcessingBit = 0; currentProcessingBit < 8; ++currentProcessingBit)
            {
                //Variable holding the raw data.
                uint8_t dataByte;
                //Repeat byte with data
                uint16_t repeatByte;
                
                if(byteFlags & 1)
                {
                    currentArchiveFileStream->read((char *) &dataByte, 1);
                    unCompressedFile->at(currentWritePosition) = dataByte;
                    currentWritePosition++;
                    byteIndex &= 0xFFF;
                    lookAheadBuffer[byteIndex] = dataByte;
                    byteIndex++;
                    currentProcessingByte++;
                }
                else
                {
                    currentArchiveFileStream->read((char *) &repeatByte, 2);
                    dataByte = (repeatByte >> 12) + 3;
                    repeatByte &= 0xFFF;
                    
                    while (dataByte--)
                    {
                        repeatByte &= 0xFFF;
                        byteIndex &= 0xFFF;
                        unCompressedFile->at(currentWritePosition) = lookAheadBuffer.at(repeatByte);
                        currentWritePosition++;
                        lookAheadBuffer.at(byteIndex) =  (lookAheadBuffer.at(repeatByte));
                        repeatByte++;
                        byteIndex++;
                        
                        currentProcessingByte++;
                        if(currentProcessingByte  == unCompressedFileLength)
                        {
                            break;
                        }
                    }
                }
                if(currentProcessingByte == unCompressedFileLength)
                {
                    break;
                }
                byteFlags >>= 1;
            }
        }
    }
    //If the data is uncompressed
    else if(compressionFlags == 0x00)
    {
        currentArchiveFileStream->read((char *) &unCompressedFile->front(), unCompressedFileLength);
    }
    //Unknown data (error)
    else
    {
        CorruptArchiveException corruptData;
        corruptData.SetErrorMessage("Archive is not a WAR archive or is corrupt");
        throw corruptData;
    }
    
    return unCompressedFile;
}

void WarArchive::ExtractEntity(std::string outFilePath, unsigned int entityNumber)
{
    std::vector<uint8_t> *unCompressedFile = NULL;
    unCompressedFile = ExtractEntity(entityNumber);
    
    //Open an output file
    std::ofstream outFile;
    outFile.open(outFilePath.c_str(), std::ios::binary);
    outFile.exceptions(std::ofstream::failbit);
    
    outFile.write((char *) &unCompressedFile->front(), unCompressedFile->size());
    
    outFile.close();
}
void ExtractEntity(std::vector<char> *uncompressedFile, unsigned int entityNumber)
{
    
}

void WarArchive::CloseArchive()
{
    if(currentArchiveFileStream)
    {
        if(currentArchiveFileStream->is_open())
        {
            currentArchiveFileStream->close();
        }
        delete currentArchiveFileStream;
        currentArchiveFileStream = NULL;
    }
}

void WarArchive::CleanArchive()
{
    CloseArchive();
    if(fileOffsets)
    {
        delete fileOffsets;
        fileOffsets = NULL;
    }
}