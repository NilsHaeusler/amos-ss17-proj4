/**
 * @file electronic_control_unit_test.cpp
 *
 * These test cases are used to ensure a proper UDS handling from the 
 * `ElectronocControlUnit`. Since this task is done via ISO-TP, ensure the 
 * kernel module for virtual CAN is enabled (`sudo modprobe vcan`), the vcan 
 * address is added (`sudo ip link add dev vcan0 type vcan`) and set up (`sudo 
 * ip link set up vcan0`) before running these tests. 
 */

#include "electronic_control_unit_test.h"
#include "electronic_control_unit.h"
#include "service_identifier.h"
#include <array>
#include <cstdint>
#include <cstring>

const std::string ECU_IDENT = "PCM";
const std::string LUA_SCRIPT = "tests/test_config_dir/testscript06.lua";
const std::string DEVICE = "vcan0";

std::uint16_t requId;
std::uint16_t respId;
std::thread ecuThread;

CPPUNIT_TEST_SUITE_REGISTRATION(ElectronicControlUnitTest);

void startEcuServer()
{
    auto script = std::make_unique<EcuLuaScript>(ECU_IDENT, LUA_SCRIPT);
    requId = script->getRequestId();
    respId = script->getResponseId();
    ElectronicControlUnit(DEVICE, std::move(script));
}

ElectronicControlUnitTest::ElectronicControlUnitTest()
{
    ecuThread = std::thread(startEcuServer);
    usleep(4000); // wait some time to ensure the thread is set up and running
}

ElectronicControlUnitTest::~ElectronicControlUnitTest()
{
    ecuThread.detach();
}

void ElectronicControlUnitTest::setUp()
{
}

void ElectronicControlUnitTest::tearDown()
{
}

void ElectronicControlUnitTest::testElectronicControlUnit()
{
    TestReceiver testReceiver(requId, respId, DEVICE);
    std::thread testThread(&IsoTpReceiver::readData, &testReceiver);
    usleep(4000); // wait some time to ensure the thread is set up and running

    IsoTpSender sender(requId, respId, DEVICE);

    {
        constexpr std::array<uint8_t, 3> tc01 = {0x7F, 0x19, 0x78};
        constexpr std::array<uint8_t, 6> expResp01 = {0xFA, 0xBF, 0xAB, 0xFA, 0xBF, 0xAB};
        testReceiver.setExpectedUdsRespData(expResp01.data(), expResp01.size());
        usleep(2000);
        sender.sendData(tc01.data(), tc01.size());
        usleep(2000);
    }

    {
        constexpr std::array<uint8_t, 3> tc02 = {0x22, 0xF1, 0x90};
        constexpr std::array<uint8_t, 20> expResp02 = {
            READ_DATA_BY_IDENTIFIER_RES, 0xF1, 0x90,
            'S', 'A', 'L', 'G', 'A', '2', 'E', 'V', '9', 'H', 'A', '2', '9', '8', '7', '8', '4'
        };
        testReceiver.setExpectedUdsRespData(expResp02.data(), expResp02.size());
        usleep(2000);
        sender.sendData(tc02.data(), tc02.size());
        usleep(2000);
    }

    {
        constexpr std::array<uint8_t, 3> tc07 = {0x19, 0x02, 0xB3};
        constexpr std::array<uint8_t, 3> expResp07 = {0x47, 0x11, 0x03};
        testReceiver.setExpectedUdsRespData(expResp07.data(), expResp07.size());
        usleep(2000);
        sender.sendData(tc07.data(), tc07.size());
        usleep(2000);
    }

    sender.closeSender();
    testReceiver.closeReceiver();
    constexpr std::array<uint8_t, 1> eof = {0x00}; // send some garbage to close the receiver
    testReceiver.setExpectedUdsRespData(eof.data(), eof.size());
    usleep(2000);
    testReceiver.proceedReceivedData(eof.data(), eof.size());
    testThread.detach();
}

/**
 * Compares the incoming response data from the corresponding `UdsReceiver` with
 * the expected internal data set. This is done by the 
 * `setExpectedUdsRespData()`-function, so invoke this routine first and wait
 * some time, to ensure the comparing data is fully copied.
 * 
 * @param buffer: the buffer with the incoming data
 * @param num_bytes: the size of the incoming data in bytes
 * @see TestReceiver::setExpectedUdsRespData()
 */
void TestReceiver::proceedReceivedData(const std::uint8_t* buffer,
                                       const std::size_t num_bytes) noexcept
{
    CPPUNIT_ASSERT(num_bytes < MAX_UDS_MSG_SIZE);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Message size don't match!", m_expNumBytes, num_bytes);

    for (size_t i = 0; i < num_bytes; i++)
    {
        CPPUNIT_ASSERT_EQUAL(m_expBufferData[i], buffer[i]);
    }
}

/**
 * Copies the expected UDS response message into the internal member fields.
 * After that, the overridden `proceedReceiveData()`-function will compare all
 * receiving results form the `UdsReceiver`-instance with the provided data set.
 * Use this function before calling `sendData()` or `proceedReceivedData()`
 * of the `IsoTpReceiver`-instance and wait some time, since this is a async task.
 * 
 * @param expBufferData: the expected UDS message response from the `UdsReceiver`
 * @param expNumBytes: the expected UDS message length form the `UdsReceiver`
 * @see TestReceiver::proceedReceivedData()
 */
void TestReceiver::setExpectedUdsRespData(const std::uint8_t* expBufferData,
                                          const std::size_t expNumBytes) noexcept
{
    m_expNumBytes = expNumBytes;
    memcpy(m_expBufferData, expBufferData, expNumBytes);
}
