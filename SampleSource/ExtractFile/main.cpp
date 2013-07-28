#include "../../Source/libwararch.hpp"

void LoadFileToVectorImageGRP(std::string filePath, std::vector<char> *destinationVector)
{
    std::fstream inputFile(filePath.c_str());
    
    inputFile.exceptions(
                         std::ifstream::badbit
                         | std::ifstream::failbit
                         | std::ifstream::eofbit);
    
    inputFile.seekg(0, std::ios::end);
    
    std::streampos length(inputFile.tellg());
    
    if (length)
    {
        inputFile.seekg(0, std::ios::beg);
        destinationVector->resize(static_cast<std::size_t>(length));
        inputFile.read((char *)&destinationVector->front(), static_cast<std::size_t>(length));
    }
}

int main()
{
    WarArchive myArchive;
    myArchive.LoadArchive("/Users/brad/Desktop/war1/DATA/DATA.WAR");
    myArchive.ExtractEntity("out.xmi", 472);
    myArchive.CloseArchive();

    //std::vector<char> *imageData = new std::vector<char>;
    //LoadFileToVectorImageGRP("/Users/brad/Desktop/war1/DATA/DATA.WAR", imageData);
    //myArchive.LoadArchive(imageData);
    
    return 0;
}