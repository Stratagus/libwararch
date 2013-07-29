#ifndef libwararch_H
#define libwararch_H
/*! \mainpage General Information
 *
 *  libwararch Motivation
 *  ================
 *  1. Extensive Documentation
 *  2. Cross Platform (Windows, Mac OSX, Linux)
 *  3. C++ (Use of OOP Techniques)\n
 *
 *  CMake Build Options
 *  ===================
 *  There are three parameters that can be modified.\n
 *  1. VERBOSE - The amount of information outputted to the console
 *      while processing WAR files and conversion.\n
 *      DEFAULT = 0 Range = [1 - 5]\n
 *      To set add the cmake flag "-DVERBOSE=[DesiredValue]"\n\n
 *  2. UNITTESTS - Compile the Boost Unit tests inluded with libwararch.
 *      This will require that the Boost Library with the Unit Test Framework Module
 *      be compiled and installed.\n To enable unit tests
 *      Add the cmake flag "-DUNITTESTS=on"\n\n
 *  3. SAMPLECODE - To compile the sample code.\n
 *      Add the cmake flag "-DSAMPLECODE=on"\n
 *
 *  Sample Code
 *  ===========
 *  Sample code can be found from the root directory folder\n
 *  "SampleSource/"
 *
 *  Credits
 *  =======
 *  1. Bradley Clemetson\n
 *      @ http://codeprogrammers.net
 *
 *  Special Thanks
 *  ==============
 *  1. Patrick Wyatt
 *      @ http://www.codeofhonor.com/blog/
 *  2. Pali Rohar
 *      @ https://launchpad.net/~pali
 */
#include "Archive/Archive.hpp"


#endif