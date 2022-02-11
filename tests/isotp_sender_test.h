/**
 * @file isotp_sender_test.h
 * 
 */

#ifndef ISOTP_SENDER_TEST_H
#define ISOTP_SENDER_TEST_H

#include <cppunit/extensions/HelperMacros.h>

class IsoTpSenderTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(IsoTpSenderTest);

    CPPUNIT_TEST(testIsoTpSender);
    CPPUNIT_TEST(testOpenSender);
    CPPUNIT_TEST(testCloseSender);
    CPPUNIT_TEST(testSendData);

    CPPUNIT_TEST_SUITE_END();

public:
    IsoTpSenderTest();
    virtual ~IsoTpSenderTest();
    void setUp();
    void tearDown();

private:
    void testIsoTpSender();
    void testOpenSender();
    void testCloseSender();
    void testSendData();

};

#endif /* ISOTP_SENDER_TEST_H */

