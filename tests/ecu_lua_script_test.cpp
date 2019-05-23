/**
 * @file ecu_lua_script_test.cpp
 *
 * Unit tests for the class `EcuLuaScript`.
 */

#include "ecu_lua_script_test.h"
#include "ecu_lua_script.h"

const std::string ECU_IDENT = "PCM";
const std::string LUA_SCRIPT = "tests/test_config_dir/testscript05.lua";

CPPUNIT_TEST_SUITE_REGISTRATION(EcuLuaScriptTest);

void EcuLuaScriptTest::setUp()
{
}

void EcuLuaScriptTest::tearDown()
{
}

void EcuLuaScriptTest::testEcuLuaScript()
{
    const std::string ecuIdent = ECU_IDENT;
    std::string luaScript = LUA_SCRIPT;

    CPPUNIT_ASSERT_NO_THROW(EcuLuaScript ecuLuaScript(ecuIdent, luaScript));

    // these tests are supposed to fail
    CPPUNIT_ASSERT_THROW(EcuLuaScript ecuLuaScript(ecuIdent, "adsf"), std::invalid_argument);
    CPPUNIT_ASSERT_THROW(EcuLuaScript ecuLuaScript("hzlpfrt", luaScript), std::invalid_argument);

    luaScript = "tests/test_config_dir/invalid_testscript01.lua";
    // no request ID
    CPPUNIT_ASSERT_THROW(EcuLuaScript ecuLuaScript("TC01", luaScript), std::invalid_argument);
    // no response ID
    CPPUNIT_ASSERT_THROW(EcuLuaScript ecuLuaScript("TC02", luaScript), std::invalid_argument);

    // no broadcast ID (default addr `0x7DF` should be loaded)
    CPPUNIT_ASSERT_NO_THROW(EcuLuaScript ecuLuaScript("TC03", luaScript));
}

void EcuLuaScriptTest::testGetRequestId()
{
    EcuLuaScript ecuLuaScript(ECU_IDENT, LUA_SCRIPT);
    std::uint16_t result = ecuLuaScript.getRequestId();
    std::uint16_t expect = 0x100;
    CPPUNIT_ASSERT_EQUAL(expect, result);
}

void EcuLuaScriptTest::testGetResponseId()
{
    EcuLuaScript ecuLuaScript(ECU_IDENT, LUA_SCRIPT);
    std::uint16_t result = ecuLuaScript.getResponseId();
    std::uint16_t expect = 0x200;
    CPPUNIT_ASSERT_EQUAL(expect, result);
}

void EcuLuaScriptTest::testGetDataByIdentifier()
{
    EcuLuaScript ecuLuaScript(ECU_IDENT, LUA_SCRIPT);
    std::uint16_t identifier = 0xf190;
    std::string expect = "SALGA2EV9HA298784";
    std::string result = ecuLuaScript.getDataByIdentifier(EcuLuaScript::toByteResponse(identifier, 2));
    CPPUNIT_ASSERT_EQUAL(expect, result);

    identifier = 0xf124;
    expect = "HPLA-12345-AB";
    result = ecuLuaScript.getDataByIdentifier(EcuLuaScript::toByteResponse(identifier, 2));
    CPPUNIT_ASSERT_EQUAL(expect, result);

    identifier = 0x1e23;
    expect = "231132";
    result = ecuLuaScript.getDataByIdentifier(EcuLuaScript::toByteResponse(identifier, 2));
    CPPUNIT_ASSERT_EQUAL(expect, result);

    // this is supposed to fail
    identifier = 0xf123;
    expect = "";
    result = ecuLuaScript.getDataByIdentifier(EcuLuaScript::toByteResponse(identifier, 2));
    CPPUNIT_ASSERT_EQUAL(expect, result);
}

void EcuLuaScriptTest::testGetSeed()
{
    EcuLuaScript ecuLuaScript(ECU_IDENT, LUA_SCRIPT);
    std::uint8_t identifier = 0x01;
    std::string expect = "0x4455";
    std::string result = ecuLuaScript.getSeed(identifier);
    CPPUNIT_ASSERT_EQUAL(expect, result);

    identifier = 0x03;
    expect = "0x6677";
    result = ecuLuaScript.getSeed(identifier);
    CPPUNIT_ASSERT_EQUAL(expect, result);

    // this is supposed to fail
    identifier = 0x02;
    expect = "";
    result = ecuLuaScript.getSeed(identifier);
    CPPUNIT_ASSERT_EQUAL(expect, result);
}

void EcuLuaScriptTest::testLiteralHexStrToBytes()
{
    EcuLuaScript ecuLuaScript(ECU_IDENT, LUA_SCRIPT);
    std::string hexString = "48 65 6c 6c 6f"; // "Hello"
    std::array<std::uint8_t, 5> expect = {0x48, 0x65, 0x6c, 0x6c, 0x6f};
    std::vector<std::uint8_t> result = ecuLuaScript.literalHexStrToBytes(hexString);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Size mismatch!", expect.size(), result.size());

    for (unsigned i = 0; i < result.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expect.at(i), result.at(i));
    }

    hexString = " 48 65 6c 6c 6"; // odd byte number
    expect = {0x48, 0x65, 0x6c, 0x6c, 0x6};
    result = ecuLuaScript.literalHexStrToBytes(hexString);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Size mismatch!", expect.size(), result.size());

    for (unsigned i = 0; i < result.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expect.at(i), result.at(i));
    }

    hexString = " 48 6h 6c gg 6f "; // not hex -> character gets ignored
    expect = {0x48, 0x6, 0x6c, 0x0, 0x6f};
    result = ecuLuaScript.literalHexStrToBytes(hexString);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Size mismatch!", expect.size(), result.size());

    for (unsigned i = 0; i < result.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expect.at(i), result.at(i));
    }
}

void EcuLuaScriptTest::testAscii()
{
    EcuLuaScript ecuLuaScript(ECU_IDENT, LUA_SCRIPT);
    std::string inputStr = "Hello";
    std::string expect = " 48 65 6C 6C 6F ";
    std::string result;

    result = ecuLuaScript.ascii(inputStr);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Size mismatch!", expect.size(), result.size());

    for (unsigned i = 0; i < result.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expect.at(i), result.at(i));
    }

    inputStr = ""; // empty string
    expect = "";
    result = ecuLuaScript.ascii(inputStr);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Size mismatch!", expect.size(), result.size());

    for (unsigned i = 0; i < result.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expect.at(i), result.at(i));
    }

    inputStr = "Möp™®"; // stressing the function with Unicode chars
    expect = " 4D C3 B6 70 E2 84 A2 C2 AE ";
    result = ecuLuaScript.ascii(inputStr);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Size mismatch!", expect.size(), result.size());

    for (unsigned i = 0; i < result.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expect.at(i), result.at(i));
    }
}

void EcuLuaScriptTest::testToByteResponse()
{
    EcuLuaScript ecuLuaScript(ECU_IDENT, LUA_SCRIPT);
    unsigned long inputValue;
    unsigned int len;
    std::string expect;
    std::string result;

    inputValue = 0x12'34'56'78;
    len = 8;
    expect = "00 00 00 00 12 34 56 78";
    result = ecuLuaScript.toByteResponse(inputValue, len);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Size mismatch!", expect.size(), result.size());
    for (unsigned i = 0; i < result.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expect.at(i), result.at(i));
    }

    inputValue = 0x12'34'56'78;
    expect = "12 34 56 78";
    result = ecuLuaScript.toByteResponse(inputValue); // no len -> 4 = default
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Size mismatch!", expect.size(), result.size());
    for (unsigned i = 0; i < result.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expect.at(i), result.at(i));
    }

    inputValue = 0x12'34'56'78;
    len = 9;
    expect = "00 00 00 00 00 12 34 56 78";
    result = ecuLuaScript.toByteResponse(inputValue, len);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Size mismatch!", expect.size(), result.size());
    for (unsigned i = 0; i < result.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expect.at(i), result.at(i));
    }

    inputValue = 0x12'34'56'78;
    len = 2;
    expect = "56 78";
    result = ecuLuaScript.toByteResponse(inputValue, len);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Size mismatch!", expect.size(), result.size());
    for (unsigned i = 0; i < result.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expect.at(i), result.at(i));
    }

    inputValue = 0xff'ff'ff'ff'ff'ff'ff'ff;
    len = 1;
    expect = "FF";
    result = ecuLuaScript.toByteResponse(inputValue, len);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Size mismatch!", expect.size(), result.size());
    for (unsigned i = 0; i < result.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expect.at(i), result.at(i));
    }

    inputValue = 0xff'ff'ff'ff;
    len = 9;
    expect = "00 00 00 00 00 FF FF FF FF";
    result = ecuLuaScript.toByteResponse(inputValue, len);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Size mismatch!", expect.size(), result.size());
    for (unsigned i = 0; i < result.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expect.at(i), result.at(i));
    }

    // len = 0 -> empty string
    inputValue = 0xff'ff'ff'ff'ff'ff'ff'ff;
    len = 0;
    expect = "";
    result = ecuLuaScript.toByteResponse(inputValue, len);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Size mismatch!", expect.size(), result.size());

    // len = -1 -> do some naughty stuff
    inputValue = 0x00;
    len = -1;

    for (int i = 0; i < 4096 - 1; ++i)
    {
        expect += "00 ";
    }
    expect += "00";

    result = ecuLuaScript.toByteResponse(inputValue, len);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Size mismatch!", static_cast<decltype(result.size())> (4096 * 3 - 1), result.size());
    for (unsigned i = 0; i < result.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expect.at(i), result.at(i));
    }

    // inputValue = -1 -> do some more naughty stuff
    inputValue = -1;
    expect = "FF FF FF FF";
    result = ecuLuaScript.toByteResponse(inputValue);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Size mismatch!", expect.size(), result.size());
    for (unsigned i = 0; i < result.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expect.at(i), result.at(i));
    }

    // and even more naughty stuff
    inputValue = -1;
    len = 512;
    expect = std::string("00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ")
            + "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 "
            + "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 "
            + "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 "
            + "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 "
            + "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 "
            + "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 "
            + "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 "
            + "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 "
            + "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 "
            + "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 "
            + "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 "
            + "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 "
            + "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 "
            + "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 "
            + "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FF FF FF FF";

    result = ecuLuaScript.toByteResponse(inputValue, len);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Size mismatch!", expect.size(), result.size());
    for (unsigned i = 0; i < result.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expect.at(i), result.at(i));
    }
}

void EcuLuaScriptTest::testGetRaw()
{
    EcuLuaScript ecuLuaScript(ECU_IDENT, LUA_SCRIPT);
    std::string identStr;
    std::string expect;
    std::string result;

    identStr = "10 02";
    expect = "50 02 00 19 01 f4";
    result = ecuLuaScript.getRaw(identStr);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Size mismatch!", expect.size(), result.size());
    for (unsigned i = 0; i < result.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expect.at(i), result.at(i));
    }

    identStr = "22 fa bc";
    expect = "10 33 11";
    result = ecuLuaScript.getRaw(identStr);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Size mismatch!", expect.size(), result.size());
    for (unsigned i = 0; i < result.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expect.at(i), result.at(i));
    }

    identStr = "22 F1 91";
    expect = "62 F1 91" + ecuLuaScript.ascii("SALGA2EV9HA298784");
    result = ecuLuaScript.getRaw(identStr);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Size mismatch!", expect.size(), result.size());
    for (unsigned i = 0; i < result.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expect.at(i), result.at(i));
    }

    identStr = "22 F1 91";
    expect = "62 F1 91 53 41 4C 47 41 32 45 56 39 48 41 32 39 38 37 38 34 ";
    result = ecuLuaScript.getRaw(identStr);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Size mismatch!", expect.size(), result.size());
    for (unsigned i = 0; i < result.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expect.at(i), result.at(i));
    }
}
