/**
 * @file ecu_lua_script_test.h
 *
 */

#ifndef ECU_LUA_SCRIPT_TEST_H
#define ECU_LUA_SCRIPT_TEST_H

#include <cppunit/extensions/HelperMacros.h>

class EcuLuaScriptTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(EcuLuaScriptTest);

    CPPUNIT_TEST(testEcuLuaScript);
    CPPUNIT_TEST(testGetRequestId);
    CPPUNIT_TEST(testGetResponseId);
    CPPUNIT_TEST(testGetDataByIdentifier);
    CPPUNIT_TEST(testGetSeed);
    CPPUNIT_TEST(testLiteralHexStrToBytes);
    CPPUNIT_TEST(testAscii);
    CPPUNIT_TEST(testToByteResponse);
    CPPUNIT_TEST(testGetRaw);

    CPPUNIT_TEST_SUITE_END();

public:
    EcuLuaScriptTest() = default;
    virtual ~EcuLuaScriptTest() = default;
    void setUp();
    void tearDown();

private:
    void testEcuLuaScript();
    void testGetRequestId();
    void testGetResponseId();
    void testGetDataByIdentifier();
    void testGetSeed();
    void testLiteralHexStrToBytes();
    void testAscii();
    void testToByteResponse();
    void testGetRaw();

};

#endif /* ECU_LUA_SCRIPT_TEST_H */

