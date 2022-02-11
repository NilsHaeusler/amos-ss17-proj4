/**
 * @file uds_receiver_test.h
 *
 */

#ifndef UDS_RECEIVER_TEST_H
#define UDS_RECEIVER_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "isotp_receiver.h"

constexpr size_t MAX_UDS_MSG_SIZE = 4096;

/**
 * Simple test receiver class to mock a responding device. Only for testing.
 */ 
class TestReceiver : public IsoTpReceiver
{
public:
    TestReceiver() = delete;

    TestReceiver(canid_t source,
                 canid_t dest,
                 const std::string& device)
    : IsoTpReceiver(source, dest, device)
    {
    }
    virtual ~TestReceiver() = default;

    void setExpectedUdsRespData(const uint8_t* expBufferData,
                                const size_t expNumBytes) noexcept;

private:
    uint8_t m_expBufferData[MAX_UDS_MSG_SIZE];
    size_t m_expNumBytes;

    void proceedReceivedData(const uint8_t* buffer,
                             const size_t num_bytes) noexcept override;

};

class UdsReceiverTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(UdsReceiverTest);

    CPPUNIT_TEST(testUdsReceiver);
    CPPUNIT_TEST(testProceedReceivedData);
    CPPUNIT_TEST(testGenerateSeed);

    CPPUNIT_TEST_SUITE_END();

public:
    UdsReceiverTest();
    virtual ~UdsReceiverTest();
    void setUp();
    void tearDown();

private:
    void testUdsReceiver();
    void testProceedReceivedData();
    void testSetSessionController();
    void testGenerateSeed();

};

#endif /* UDS_RECEIVER_TEST_H */
