#include "main.hpp"
#include "../../Source/libwararch.hpp"

int main()
{
    //Create a WarArchive data structure
    WarArchive myArchive;
    
    //Load a war archive (In my case the Warcraft 1 file DATA.WAR)
    myArchive.LoadArchive("war1.war");
    
    //The entity is extracted and directly written to disk
    myArchive.ExtractEntity("out.wav", 473);
    
    //A vector with the uncompressed file can also be extracted
    //for further processing
    std::vector<uint8_t> *doorOpenSoundData;
    doorOpenSoundData = myArchive.ExtractEntity(473);

    //Clean up our vector of uncompressed data
    //Since we are not doing any more processing with it
    doorOpenSoundData->resize(0);
    delete doorOpenSoundData;
    doorOpenSoundData = nullptr;
    
    //Close the WAR archive and delete internal data structures
    myArchive.CleanArchive();
    
    return 0;
}