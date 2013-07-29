libwararch
======

A simple library to extract files from Blizzard's WAR archive format
 
libwararch Motivation
================
1. Extensive Documentation
2. Cross Platform (Windows, Mac OSX, Linux)
3. C++ (Use of OOP Techniques)

CMake Build Options
===================
There are three parameters that can be modified.
1. VERBOSE - The amount of information outputted to the console
 while processing GRP files and ColorPalettes.
 DEFAULT = 0 Range = [1 - 5]

 To set add the cmake flag "-DVERBOSE=[DesiredValue]"

2. UNITTESTS - Compile the Boost Unit tests inluded with libwararch.
 This will require that the Boost Library with the Unit Test Framework Module
 be compiled and installed. To enable unit tests

 Add the cmake flag "-DUNITTESTS=on"

3. SAMPLECODE - To compile the sample code.

 Add the cmake flag "-DSAMPLECODE=on"
 
 
Sample Code
===========
Sample code can be found from the root directory folder
"SampleSource/"

Credits
=======
1. Bradley Clemetson
 @ http://codeprogrammers.net


Special Thanks
==============
1. Patrick Wyatt
 @ http://www.codeofhonor.com/blog/
2. Pali Rohar
 @ https://launchpad.net/~pali