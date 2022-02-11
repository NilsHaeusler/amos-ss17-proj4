/** 
 * @file sevice_identifier.h
 *
 * This files defines the UDS service identifier. The info is adopted from
 * https://en.wikipedia.org/wiki/Unified_Diagnostic_Services
 */

#ifndef SEVICE_IDENTIFIER_H
#define SEVICE_IDENTIFIER_H

#include <cstdint>

#define SESSION_TIME 5000

// Function Group: Diagnostic and Communications Management
constexpr uint8_t DIAGNOSTIC_SESSION_CONTROL_REQ = 0x10;
constexpr uint8_t DIAGNOSTIC_SESSION_CONTROL_RES = 0x50;

constexpr uint8_t ECU_RESET_REQ = 0x11;
constexpr uint8_t ECU_RESET_RES = 0x51;

constexpr uint8_t SECURITY_ACCESS_REQ = 0x27;
constexpr uint8_t SECURITY_ACCESS_RES = 0x67;

constexpr uint8_t COMMUNICATION_CONTROL_REQ = 0x28;
constexpr uint8_t COMMUNICATION_CONTROL_RES = 0x68;

constexpr uint8_t TESTER_PRESENT_REQ = 0x3E;
constexpr uint8_t TESTER_PRESENT_RES = 0x7E;

constexpr uint8_t ACCESS_TIMING_PARAMETERS_REQ = 0x83;
constexpr uint8_t ACCESS_TIMING_PARAMETERS_RES = 0xC3;

constexpr uint8_t SECURED_DATA_TRANSMISSION_REQ = 0x84;
constexpr uint8_t SECURED_DATA_TRANSMISSION_RES = 0xC4;

constexpr uint8_t CONTROL_DTC_SETTINGS_REQ = 0x85;
constexpr uint8_t CONTROL_DTC_SETTINGS_RES = 0xC5;

constexpr uint8_t RESPONSE_ON_EVENT_REQ = 0x86;
constexpr uint8_t RESPONSE_ON_EVENT_RES = 0xC6;

constexpr uint8_t LINK_CONTROL_REQ = 0x87;
constexpr uint8_t LINK_CONTROL_RES = 0xC7;

// Function Group: Data Transmission
constexpr uint8_t READ_DATA_BY_IDENTIFIER_REQ = 0x22; ///< RDBI
constexpr uint8_t READ_DATA_BY_IDENTIFIER_RES = 0x62; ///< RDBIPR

constexpr uint8_t READ_MEMORY_BY_ADDRESS_REQ = 0x23;
constexpr uint8_t READ_MEMORY_BY_ADDRESS_RES = 0x63;

constexpr uint8_t READ_SCALING_DATA_BY_IDENTIFIER_REQ = 0x24;
constexpr uint8_t READ_SCALING_DATA_BY_IDENTIFIER_RES = 0x64;

constexpr uint8_t READ_DATA_BY_IDENTIFIER_PERIODIC_REQ = 0x2A;
constexpr uint8_t READ_DATA_BY_IDENTIFIER_PERIODIC_RES = 0x6A;

constexpr uint8_t DYNAMICALLY_DEFINE_DATA_IDENTIFIER_REQ = 0x2C;
constexpr uint8_t DYNAMICALLY_DEFINE_DATA_IDENTIFIER_RES = 0x6C;

constexpr uint8_t WRITE_DATA_BY_IDENTIFIER_REQ = 0x2E;
constexpr uint8_t WRITE_DATA_BY_IDENTIFIER_RES = 0x6E;

constexpr uint8_t WRITE_MEMORY_BY_ADDRESS_REQ = 0x3D;
constexpr uint8_t WRITE_MEMORY_BY_ADDRESS_RES = 0x7D;

// Function Group: Stored Data Transmission
constexpr uint8_t CLEAR_DIAGNOSTIC_INFORMATION_REQ = 0x14;
constexpr uint8_t CLEAR_DIAGNOSTIC_INFORMATION_RES = 0x54;

constexpr uint8_t READ_DTC_INFORMATION_REQ = 0x19;
constexpr uint8_t READ_DTC_INFORMATION_RES = 0x59;

// Function Group: Input / Output Control
constexpr uint8_t INPUT_OUTPUT_CONTROL_BY_IDENTIFIER_REQ = 0x2f;
constexpr uint8_t INPUT_OUTPUT_CONTROL_BY_IDENTIFIER_RES = 0x6f;

// Function Group: Remote Activation of Routine
constexpr uint8_t ROUTINE_CONTROL_REQ = 0x31;
constexpr uint8_t ROUTINE_CONTROL_RES = 0x71;

// Function Group: Upload / Download
constexpr uint8_t REQUEST_DOWNLOAD_REQ = 0x34;
constexpr uint8_t REQUEST_DOWNLOAD_RES = 0x74;

constexpr uint8_t REQUEST_UPLOAD_REQ = 0x35;
constexpr uint8_t REQUEST_UPLOAD_RES = 0x75;

constexpr uint8_t TRANSFER_DATA_REQ = 0x36;
constexpr uint8_t TRANSFER_DATA_RES = 0x76;

constexpr uint8_t REQUEST_TRANSFER_EXIT_REQ = 0x37;
constexpr uint8_t REQUEST_TRANSFER_EXIT_RES = 0x77;

constexpr uint8_t REQUEST_FILE_TRANSFER_REQ = 0x38;
constexpr uint8_t REQUEST_FILE_TRANSFER_RES = 0x78;

// Function Group: Error
constexpr uint8_t ERROR = 0x7F;
constexpr uint8_t SERVICE_NOT_SUPPORTED = 0x11;
constexpr uint8_t SUBFUNCTION_NOT_SUPPORTED = 0x12;
constexpr uint8_t INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT = 0x13; ///< IMLOIF
constexpr uint8_t RESPONSE_TOO_LONG = 0x14; ///< RTL
constexpr uint8_t CONDITIONS_NOT_CORRECT = 0x22; ///< CNC
constexpr uint8_t REQUEST_OUT_OF_RANGE = 0x31; ///< ROOR
constexpr uint8_t SECURITY_ACCESS_DENIED = 0x33; ///< SAD

#endif /* SEVICE_IDENTIFIER_H */
