/**
 * @file utils_test.h
 *
 */

#ifndef UTILSTEST_H
#define UTILSTEST_H

#include <cppunit/extensions/HelperMacros.h>

class UtilsTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(UtilsTest);

    CPPUNIT_TEST(testExistsFile);
    CPPUNIT_TEST(testExistsDirectory);
    CPPUNIT_TEST(testEndsWith);
    CPPUNIT_TEST(testGetConfigFilenames);

    CPPUNIT_TEST_SUITE_END();

public:
    UtilsTest() = default;
    virtual ~UtilsTest() = default;
    void setUp();
    void tearDown();

private:
    void testExistsFile();
    void testExistsDirectory();
    void testEndsWith();
    void testGetConfigFilenames();

};

#endif /* UTILSTEST_H */

