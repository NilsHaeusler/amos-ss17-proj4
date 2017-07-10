/**
 * @file electronic_control_unit.cpp
 *
 * This file contains a class which constitutes a Electronic Control Unit (ECU).
 */

#include "electronic_control_unit.h"
#include <array>
#include <unistd.h>

using namespace std;

ElectronicControlUnit::ElectronicControlUnit(const string& device, EcuLuaScript&& ecuScript)
: sender_(ecuScript.getRequestId(), ecuScript.getResponseId(), device)
, udsReceiver_(ecuScript.getRequestId(), ecuScript.getResponseId(), device, move(ecuScript), sender_, &sessionControl_)
, broadcastReceiver_(ecuScript.getBroadcastId(), device, &udsReceiver_, &sessionControl_)
, udsReceiverThread_(&IsoTpReceiver::readData, &udsReceiver_)
, broadcastReceiverThread_(&IsoTpReceiver::readData, &broadcastReceiver_)
{
    ecuScript.setSessionController(&sessionControl_);
}

ElectronicControlUnit::~ElectronicControlUnit()
{
    broadcastReceiverThread_.join();
    udsReceiverThread_.join();
}
