/**
 * @file isotp_sender_test.cpp
 *
 */

#include "isotp_sender_test.h"
#include "isotp_sender.h"
#include <unistd.h>

constexpr canid_t SOURCE_ADDR = 0x100;
constexpr canid_t DEST_ADDR = 0x200;
const std::string DEVICE = "vcan0";

CPPUNIT_TEST_SUITE_REGISTRATION(IsoTpSenderTest);

IsoTpSenderTest::IsoTpSenderTest()
{
}

IsoTpSenderTest::~IsoTpSenderTest()
{
}

void IsoTpSenderTest::setUp()
{
}

void IsoTpSenderTest::tearDown()
{
}

void IsoTpSenderTest::testIsoTpSender()
{
    int expect;
    int result;
    std::array<uint8_t, 2> trash = {0x01, 0x02};

    IsoTpSender* pIsoTpSender1;
    CPPUNIT_ASSERT_NO_THROW(pIsoTpSender1 = new IsoTpSender(SOURCE_ADDR, DEST_ADDR, DEVICE));
    expect = 2;
    result = pIsoTpSender1->sendData(trash.data(), trash.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Sending on instance 1 failed!", expect, result);

    IsoTpSender* pIsoTpSender2;
    CPPUNIT_ASSERT_NO_THROW(pIsoTpSender2 = new IsoTpSender(SOURCE_ADDR, DEST_ADDR, DEVICE));
    expect = 2;
    result = pIsoTpSender2->sendData(trash.data(), trash.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Sending on instance 2 failed!", expect, result);

    delete pIsoTpSender1;
    delete pIsoTpSender2;
}

void IsoTpSenderTest::testOpenSender()
{
    IsoTpSender isoTpSender(SOURCE_ADDR, DEST_ADDR, DEVICE);
    std::array<uint8_t, 2> trash = {0x01, 0x02};

    isoTpSender.closeSender();
    int expect = -1;
    int result = isoTpSender.sendData(trash.data(), trash.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Sending on closed socket should not be possible!", expect, result);

    expect = 0;
    result = isoTpSender.openSender();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Opening socket failed!", expect, result);

    expect = 2;
    result = isoTpSender.sendData(trash.data(), trash.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Sending on opened socket failed!", expect, result);
}

void IsoTpSenderTest::testCloseSender()
{
    IsoTpSender isoTpSender(SOURCE_ADDR, DEST_ADDR, DEVICE);
    std::array<uint8_t, 2> trash = {0x01, 0x02};
    int expect = 2;
    int result = isoTpSender.sendData(trash.data(), trash.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Sending on opened socket failed!", expect, result);

    isoTpSender.closeSender();

    expect = -1;
    result = isoTpSender.sendData(trash.data(), trash.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Sending on closed socket should not be possible!", expect, result);
}

void IsoTpSenderTest::testSendData()
{
    int expect;
    int result;
    IsoTpSender isoTpSender(SOURCE_ADDR, DEST_ADDR, DEVICE);

    std::array<std::uint8_t, 5> tc01 = {0x01, 0x02, 0x03, 0x04, 0x05};
    expect = 5;
    result = isoTpSender.sendData(tc01.data(), tc01.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("01 Size mismatch!", expect, result);

    std::vector<std::uint8_t> tc02(4096, 0x05); // boundary test for max UDS message size  
    expect = 4096;
    result = isoTpSender.sendData(tc02.data(), tc02.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("02 Size mismatch!", expect, result);

    // these tests are supposed to fail
    std::vector<std::uint8_t> tc03(4097, 0x06); // UDS message size exceeds 4096 bytes  
    expect = 0;
    result = isoTpSender.sendData(tc03.data(), tc03.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("03 Size mismatch!", expect, result);

    isoTpSender.closeSender(); // sending with closed socket
    expect = -1;
    result = isoTpSender.sendData(tc01.data(), tc01.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("04 Size mismatch!", expect, result);
}

