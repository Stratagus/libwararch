#include "APITest.hpp"

BOOST_AUTO_TEST_SUITE(ArchiveTests)

BOOST_AUTO_TEST_CASE(GetNumberOfEntitiesFail)
{
    WarArchive myArch;
    BOOST_REQUIRE_THROW(myArch.GetNumberOfEntities(), NoArchiveLoadedException);
}

BOOST_AUTO_TEST_CASE(ExtractEntityFail)
{
    WarArchive myArch;
    BOOST_REQUIRE_THROW(myArch.ExtractEntity(0), NoArchiveLoadedException);
}

BOOST_AUTO_TEST_CASE(ExtractEntityFileFail)
{
    WarArchive myArch;
    BOOST_REQUIRE_THROW(myArch.ExtractEntity("file.out", 0), NoArchiveLoadedException);
}

BOOST_AUTO_TEST_CASE(ExtractEntityOutofBoundsFail)
{
    WarArchive myArch;
    myArch.LoadArchive(SAMPLEARCHIVE);
    BOOST_REQUIRE_THROW(myArch.ExtractEntity(INT_MAX), InvalidEntityException);
}

BOOST_AUTO_TEST_CASE(LoadPathFAIL)
{
    WarArchive myArch;
    BOOST_REQUIRE_THROW(myArch.LoadArchive("sdas/sadasd/we/23--23"), std::exception);
}

BOOST_AUTO_TEST_CASE(CleanData)
{
    WarArchive myArch;
    for (int currentClean = 0; currentClean < 5; currentClean++)
    {
        myArch.CleanArchive();
    }
    BOOST_ASSERT(true);
}
BOOST_AUTO_TEST_SUITE_END()