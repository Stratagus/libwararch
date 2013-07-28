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
        throw "bad";
    #warning throw here
    }
    
    //Open an output file
    std::ofstream outFile;
    outFile.open(outFilePath.c_str(), std::ios::binary);
    outFile.exceptions(std::ofstream::failbit);
    
    
    //unknown
    unsigned int flags;
    int bytesProcessed = 0;
    

    
    currentArchiveFileStream->seekg(fileOffsets->at(entityNumber));
    
    unsigned int unCompressedFileLength;
    currentArchiveFileStream->read((char *) &unCompressedFileLength, 4);
    
    flags = (unCompressedFileLength >> 24);
    unCompressedFileLength &= 0x00FFFFFF;
    std::vector<uint8_t> buffer;
    //The data is compressed
    if(flags == 0x20)
    {
        
        
        //Arbitary?
        buffer.resize(4096);
        
        int byteIndex = 0;
        
        
        while(bytesProcessed < unCompressedFileLength)
        {
            uint8_t bflags;
            //std::cout << "B Flags: " << (int) bflags << " Next value :" << (int) currentArchiveFileStream->peek() << '\n';
            currentArchiveFileStream->read((char *) &bflags, 1);
            //std::cout << "B Flags: " << (int) bflags << " Next value :" << (int) currentArchiveFileStream->peek() << '\n';
            for(int i= 0; i < 8; ++i)
            {
                uint8_t j;
                uint16_t o;
                
                if(bflags & 1)
                {
                    currentArchiveFileStream->read((char *) &j, 1);
                   // std::cout << "J: " << (int) j << '\n';
                    outFile.write((char *) &j, 1);
                    buffer[byteIndex++ & 0xFFF] = j;
                    bytesProcessed++;
                    //std::cout << "Changed value of buffer to: " << (int) buffer[byteIndex & 0xFFF] << '\n';
                    
                }
                else
                {
                    currentArchiveFileStream->read((char *) &o, 2);
                    std::cout << "O Value: " << (int) o << '\n';
                    j = (o >> 12) + 3;
                    std::cout << "J Value: " << (int) j << '\n';
                    o &= 0xFFF;
                    while (j--)
                    {
                        std::cout << "buffer[o & 0xFFF]: " << (int) buffer[o++ & 0xFFF];
                        outFile.write((char *) &buffer[o & 0xFFF], 1);
                        buffer[byteIndex++ & 0xFFF] = buffer[o & 0xFFF];
                        bytesProcessed++;
                        
                        if(bytesProcessed  == unCompressedFileLength)
                        {
                            break;
                        }
                    }
                }
                
                if(bytesProcessed == unCompressedFileLength)
                {
                    break;
                }
                bflags >>= 1;
                //std::cout << "Bflags is now: " << (int) bflags << '\n';
            }
        }
        
    }
    else if(flags == 0x00)
    {
        //outFile.write((char *) , <#streamsize __n#>)
        currentArchiveFileStream->read((char *) &outFile, unCompressedFileLength);
    }
    else
    {
        throw "problem";
    }
    
    //outFile.write((char *) &output, output.size());
    
    //for(int checker = 0; checker < unCompressedFileLength; checker++)
    //{
    //    outFile.write((char *) output.at(checker), 1);
    //}
    
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