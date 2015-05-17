#pragma once

#include "../../Source/libwararch.hpp"

//Main boost include
#include <boost/test/unit_test.hpp>
#include <limits>

#ifdef __APPLE__
#define SAMPLEARCHIVE "../../Documentation/SampleContent/SampleArchive.war"
#else
#define SAMPLEARCHIVE "../Documentation/SampleContent/SamplePalette.pal"
#endif