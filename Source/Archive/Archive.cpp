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

void WarArchive::ExtractEntity(const std::string &outFilePath, unsigned int entityNumber)
{
    if(entityNumber > numberOfEntities)
    {
        //throw out of bounds error
#warning throw here
    }
    
    //unknown
    int flags;
    
    std::ofstream outFile;
    outFile.open(outFilePath.c_str(), std::ios::binary);
    outFile.exceptions(std::ofstream::failbit);
    
    currentArchiveFileStream->seekg(fileOffsets->at(entityNumber));
    
    int unCompressedFileLength;
    currentArchiveFileStream->read((char *) &unCompressedFileLength, 3);
    
    //??
#warning - 1 is a hack
    flags = (unCompressedFileLength >> 10) - 1;
    unCompressedFileLength &= 0x00FFFFFF;
    
    //The data is compressed
    if(flags == 0x20)
    {
        uint8_t ep;
        int bi = 0;
        
        for(int currentCompressedByte = 0; currentCompressedByte < unCompressedFileLength;)
        {
            uint16_t bflags;
            
            currentArchiveFileStream->read((char *) &bflags, 1);
            std::cout << "Bflags " << (int) bflags << '\n';
            
            for(int currentUncompressedByte = 0; currentUncompressedByte < 8;)
            {
                uint8_t j;
                int o;
                
                if(bflags & 1)
                {
                    currentArchiveFileStream->read((char *) &j, 1);
                    outFile.write((char *) &j, 1);
                    
                    
                }
                else
                {
                    currentArchiveFileStream->read((char *) &o, 2);
                    j = (o >> 12) + 3;
                    o &= 0xFFF;
                }
                bflags >>= 1;
            }
        }
        
    }
    //The data is uncompressed
    else if(flags == 0x00)
    {
        currentArchiveFileStream->read((char *) &outFile, unCompressedFileLength);
    }
    //Problem we don't know what the flag means : |
    else
    {
        //throw error
    #warning throw error
        throw "fail";
    }
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