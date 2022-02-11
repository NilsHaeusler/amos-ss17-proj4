/**
 * @file uds_receiver_test.cpp
 *
 * These test cases are used to ensure a proper UDS response from the 
 * `UdsReceiver`. Since this task is done via ISO-TP, ensure the kernel module
 * for virtual CAN is enabled (`sudo modprobe vcan`), the vcan address is added 
 * (`sudo ip link add dev vcan0 type vcan`) and set up (`sudo ip link set up 
 * vcan0`) before running these tests. 
 */

#include "uds_receiver_test.h"
#include "uds_receiver.h"
#include "service_identifier.h"
#include <thread>
#include <unistd.h>
#include <cstring>
#include <iomanip>

const std::string DEVICE = "vcan0";
const std::string ECU_IDENT = "PCM";
const std::string LUA_SCRIPT = "tests/test_config_dir/testscript06.lua";

CPPUNIT_TEST_SUITE_REGISTRATION(UdsReceiverTest);

UdsReceiverTest::UdsReceiverTest()
{
}

UdsReceiverTest::~UdsReceiverTest()
{
}

void UdsReceiverTest::setUp()
{
}

void UdsReceiverTest::tearDown()
{
}

void UdsReceiverTest::testUdsReceiver()
{
    auto ecuScript = std::make_unique<EcuLuaScript>(ECU_IDENT, LUA_SCRIPT);
    const uint16_t respId = ecuScript->getResponseId();
    const uint16_t requId = ecuScript->getRequestId();
    IsoTpSender sender(respId, requId, DEVICE);
    SessionController sesCtrl;
    UdsReceiver* udsReceiver;
    CPPUNIT_ASSERT_NO_THROW(udsReceiver = new UdsReceiver(requId, respId, DEVICE, std::move(ecuScript), &sender, &sesCtrl));
    delete udsReceiver;
}

void UdsReceiverTest::testProceedReceivedData()
{
    uint8_t* buffer;
    size_t num_bytes;
    auto ecuScript = std::make_unique<EcuLuaScript>(ECU_IDENT, LUA_SCRIPT);
    const uint16_t respId = ecuScript->getResponseId();
    const uint16_t requId = ecuScript->getRequestId();
    IsoTpSender sender(respId, requId, DEVICE);
    SessionController sesCtrl;
    UdsReceiver udsReceiver(requId, respId, DEVICE, std::move(ecuScript), &sender, &sesCtrl);
    TestReceiver testReceiver(requId, respId, DEVICE);
    std::thread testThread(&IsoTpReceiver::readData, &testReceiver); // run async in thread
    usleep(4000); // wait some time to ensure the thread is set up and running

    {
        constexpr std::array<uint8_t, 3> readDataById01 = {0x22, 0xf1, 0x90};
        constexpr std::array<uint8_t, 20> expAnswer01 = {
            READ_DATA_BY_IDENTIFIER_RES, 0xf1, 0x90,
            'S', 'A', 'L', 'G', 'A', '2', 'E', 'V', '9', 'H', 'A', '2', '9', '8', '7', '8', '4'
        };
        testReceiver.setExpectedUdsRespData(expAnswer01.data(), expAnswer01.size());
        usleep(4000);
        buffer = (uint8_t*) readDataById01.data();
        num_bytes = readDataById01.size();
        udsReceiver.proceedReceivedData(buffer, num_bytes);
        usleep(4000);
    }

    {
        constexpr std::array<uint8_t, 3> readDataById02 = {0x22, 0xf1, 0x24};
        constexpr std::array<uint8_t, 16> expAnswer02 = {
            READ_DATA_BY_IDENTIFIER_RES, 0xf1, 0x24,
            'H', 'P', 'L', 'A', '-', '1', '2', '3', '4', '5', '-', 'A', 'B'
        };
        testReceiver.setExpectedUdsRespData(expAnswer02.data(), expAnswer02.size());
        usleep(4000);
        buffer = (uint8_t*) readDataById02.data();
        num_bytes = readDataById02.size();
        udsReceiver.proceedReceivedData(buffer, num_bytes);
        usleep(4000);
    }

    {
        constexpr std::array<uint8_t, 3> readDataById03 = {0x22, 0xf1, 0x23};
        constexpr std::array<uint8_t, 2> expAnswer03 = {
            ERROR, REQUEST_OUT_OF_RANGE
        };
        testReceiver.setExpectedUdsRespData(expAnswer03.data(), expAnswer03.size());
        usleep(4000);
        buffer = (uint8_t*) readDataById03.data();
        num_bytes = readDataById03.size();
        udsReceiver.proceedReceivedData(buffer, num_bytes);
        usleep(4000);
    }

    {
        constexpr std::array<uint8_t, 3> readDataById04 = {0x22, 0x1e, 0x23};
        constexpr std::array<uint8_t, 9> expAnswer04 = {
            READ_DATA_BY_IDENTIFIER_RES, 0x1e, 0x23,
            '2', '3', '1', '1', '3', '2'
        };
        testReceiver.setExpectedUdsRespData(expAnswer04.data(), expAnswer04.size());
        usleep(4000);
        buffer = (uint8_t*) readDataById04.data();
        num_bytes = readDataById04.size();
        udsReceiver.proceedReceivedData(buffer, num_bytes);
        usleep(4000);
    }

    {
        constexpr std::array<uint8_t, 3> readDataById05 = {0x19, 0x02, 0xb1};
        constexpr std::array<uint8_t, 7> expAnswer05 = {
            0x59, 0x02, 0xFF, 0xE3, 0x00, 0x54, 0x2E
        };
        testReceiver.setExpectedUdsRespData(expAnswer05.data(), expAnswer05.size());
        usleep(4000);
        buffer = (uint8_t*) readDataById05.data();
        num_bytes = readDataById05.size();
        udsReceiver.proceedReceivedData(buffer, num_bytes);
        usleep(4000);
    }

    {
        constexpr std::array<uint8_t, 3> readDataById06 = {0x19, 0x02, 0xb2};
        constexpr std::array<uint8_t, 3> expAnswer06 = {
            0x47, 0x11, 0x01
        };
        testReceiver.setExpectedUdsRespData(expAnswer06.data(), expAnswer06.size());
        usleep(4000);
        buffer = (uint8_t*) readDataById06.data();
        num_bytes = readDataById06.size();
        udsReceiver.proceedReceivedData(buffer, num_bytes);
        usleep(4000);
    }

    {
        constexpr std::array<uint8_t, 3> readDataById07 = {0x19, 0x02, 0xb3};
        constexpr std::array<uint8_t, 3> expAnswer07 = {
            0x47, 0x11, 0x03
        };
        testReceiver.setExpectedUdsRespData(expAnswer07.data(), expAnswer07.size());
        usleep(4000);
        buffer = (uint8_t*) readDataById07.data();
        num_bytes = readDataById07.size();
        udsReceiver.proceedReceivedData(buffer, num_bytes);
        usleep(4000);
    }

    {
        constexpr std::array<uint8_t, 3> readDataById08 = {0x19, 0x02, 0xaf};
        constexpr std::array<uint8_t, 3> expAnswer08_1 = {0x7F, 0x19, 0x78};
        constexpr std::array<uint8_t, 7> expAnswer08_2 = {
            0x59, 0x02, 0xFF, 0xE3, 0x00, 0x54, 0x2F
        };
        testReceiver.setExpectedUdsRespData(expAnswer08_1.data(), expAnswer08_1.size());
        usleep(4000);
        buffer = (uint8_t*) readDataById08.data();
        num_bytes = readDataById08.size();

        /* Since there is a 4 second sleep in-between two send commands inside the 
         * Lua file, we need some thread ballet to test this case.
         */
        std::thread asyncThr(&UdsReceiver::proceedReceivedData, &udsReceiver, buffer, num_bytes);
        usleep(4000);
        testReceiver.setExpectedUdsRespData(expAnswer08_2.data(), expAnswer08_2.size());
        testReceiver.closeReceiver();
        asyncThr.join();
    }

    testReceiver.closeReceiver();
    constexpr std::array<uint8_t, 1> eof = {0x00}; // send some garbage to close the receiver
    udsReceiver.proceedReceivedData(eof.data(), eof.size());
    testThread.join();
}

void UdsReceiverTest::testGenerateSeed()
{
    /* Testing a random number generator is somehow pointless. However, this is
     * a simple check to proof that out of N numbers, at least one is not
     * identical with the rest of the generated number set.
     */
    constexpr int N = 64;
    std::array<uint16_t, N> randomNumbers;
    for (size_t i = 0; i < randomNumbers.size(); i++)
    {
        // fill array with random numbers
        randomNumbers[i] = UdsReceiver::generateSeed();
    }

    auto ref = randomNumbers[0]; // first number is the reference to check
    size_t counter = 1; // start at 1 to skip the reference value
    for (size_t i = 1; i < randomNumbers.size(); i++)
    {
        if (ref != randomNumbers[i])
        {
            break;
        }
        ++counter;
    }

    if (counter == N)
    {
        CPPUNIT_ASSERT_MESSAGE("The entire set of random numbers are identical!", false);
    }
    else
    {
        CPPUNIT_ASSERT(true);
    }
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
