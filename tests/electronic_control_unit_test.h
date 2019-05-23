/**
 * @file electronic_control_unit_test.h
 *
 */

#ifndef ELECTRONIC_CONTROL_UNIT_TEST_H
#define ELECTRONIC_CONTROL_UNIT_TEST_H

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

    void setExpectedUdsRespData(const std::uint8_t* expBufferData,
                                const std::size_t expNumBytes) noexcept;

    void proceedReceivedData(const std::uint8_t* buffer,
                             const std::size_t num_bytes) noexcept override;

private:
    std::uint8_t m_expBufferData[MAX_UDS_MSG_SIZE];
    std::size_t m_expNumBytes;
};

class ElectronicControlUnitTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(ElectronicControlUnitTest);

    CPPUNIT_TEST(testElectronicControlUnit);

    CPPUNIT_TEST_SUITE_END();

public:
    ElectronicControlUnitTest();
    virtual ~ElectronicControlUnitTest();
    void setUp();
    void tearDown();

private:
    void testElectronicControlUnit();

};

#endif /* ELECTRONIC_CONTROL_UNIT_TEST_H */

