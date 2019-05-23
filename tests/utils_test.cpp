/**
 * @file utils_test.cpp
 *
 * Unit test for the utility functions.
 */

#include "utils_test.h"
#include "utilities.h"
#include <algorithm>
#include <vector>

CPPUNIT_TEST_SUITE_REGISTRATION(UtilsTest);

void UtilsTest::setUp() { }

void UtilsTest::tearDown() { }

void UtilsTest::testExistsFile()
{
    const std::string file_path = "tests/test_config_dir/testscript06.lua";
    bool result = utils::existsFile(file_path);
    CPPUNIT_ASSERT_MESSAGE("File does not exist!", result);

    // these checks are supposed to fail
    result = utils::existsFile("tests/");
    CPPUNIT_ASSERT_EQUAL(false, result);

    result = utils::existsFile("tests/hutzlpfrt.lua");
    CPPUNIT_ASSERT_EQUAL(false, result);
}

void UtilsTest::testExistsDirectory()
{
    const std::string dir_path = "tests";
    bool result = utils::existsDirectory(dir_path);
    CPPUNIT_ASSERT_MESSAGE("Directory does not exist!", result);

    result = utils::existsDirectory("tests/"); // check also case with trailing slash
    CPPUNIT_ASSERT_MESSAGE("Failure on path with trailing '/'", result);

    result = utils::existsDirectory("./");
    CPPUNIT_ASSERT_EQUAL(true, result);

    result = utils::existsDirectory("..");
    CPPUNIT_ASSERT_EQUAL(true, result);

    // this check is supposed to fail
    result = utils::existsDirectory("tests/test_config_dir/testscript06.lua");
    CPPUNIT_ASSERT_EQUAL(false, result);
}

void UtilsTest::testEndsWith()
{
    bool result;

    // default case
    result = utils::endsWith("some_word", "_word");
    CPPUNIT_ASSERT_EQUAL(true, result);

    // empty word
    result = utils::endsWith("", "foo");
    CPPUNIT_ASSERT_EQUAL(false, result);

    // empty end
    result = utils::endsWith("foo", "");
    CPPUNIT_ASSERT_EQUAL(true, result);

    // end longer than word
    result = utils::endsWith("foo", "barfoo");
    CPPUNIT_ASSERT_EQUAL(false, result);

    // same length of word and end
    result = utils::endsWith("barfoo", "barfoo");
    CPPUNIT_ASSERT_EQUAL(true, result);
    result = utils::endsWith("foobar", "barfoo");
    CPPUNIT_ASSERT_EQUAL(false, result);
}

void UtilsTest::testGetConfigFilenames()
{
    std::vector<std::string> expected = {
        "PCM.lua",
        "testscript03.lua",
        "testscript04.lua",
        "testscript05.lua",
        "testscript06.lua",
        "invalid_testscript01.lua"
    };
    std::sort(expected.begin(), expected.end());

    std::vector<std::string> filenames;
    bool result;
    std::string dir;

    dir = "tests/test_config_dir";
    filenames = utils::getConfigFilenames(dir);
    std::sort(filenames.begin(), filenames.end());
    result = (expected == filenames);
    CPPUNIT_ASSERT_EQUAL(true, result);

    dir = "tests/test_config_dir/";
    filenames = utils::getConfigFilenames(dir);
    std::sort(filenames.begin(), filenames.end());
    result = (expected == filenames);
    CPPUNIT_ASSERT_EQUAL(true, result);

    dir = "tests/not_a_dir";
    filenames = utils::getConfigFilenames(dir);
    std::sort(filenames.begin(), filenames.end());
    result = (expected == filenames);
    CPPUNIT_ASSERT_EQUAL(false, result);
}
