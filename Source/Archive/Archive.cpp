#include "Archive.hpp"

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
    currentArchiveFileStream->read((char *) &numberOfFiles, 2);
    //Read in the types
    currentArchiveFileStream->read((char *) &type, 2);
    
    if(!fileOffsets)
    {
        fileOffsets = new std::vector<uint32_t>;
    }
    fileOffsets->resize(numberOfFiles);
    
    for(int currentGetFileOffset = 0; currentGetFileOffset < numberOfFiles; currentGetFileOffset++)
    {
        currentArchiveFileStream->read((char *) &fileOffsets->at(currentGetFileOffset), 4);
        char test2 = fileOffsets->at(currentGetFileOffset);
    }
    
    
}

void WarArchive::CleanArchive()
{
    if(currentArchiveFileStream)
    {
        delete currentArchiveFileStream;
        currentArchiveFileStream = NULL;
    }
    if(fileOffsets)
    {
        delete fileOffsets;
        fileOffsets = NULL;
    }
}