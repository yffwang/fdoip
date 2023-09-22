#ifndef FDOIP_V1_ENUMERATION_TYPES_HPP_
#define FDOIP_V1_ENUMERATION_TYPES_HPP_

#include <cstdint>

namespace fdoip_v1 {

enum class payload_type_e : uint16_t {
    GH_PT_NACK = 0x0000,
    GH_PT_VEHICLE_IDENTIFICATION_REQ = 0x0001,
    GH_PT_VEHICLE_IDENTIFICATION_EID_REQ = 0x0002,
    GH_PT_VEHICLE_IDENTIFICATION_VIN_REQ = 0x0003,
    GH_PT_VEHICLE_IDENTIFICATION_RES = 0x0004,          // Vehicle Announcement Message
    GH_PT_ROUTING_ACTIVATION_REQ = 0x0005,
    GH_PT_ROUTING_ACTIVATION_RES = 0x0006,
    GH_PT_ALIVE_CHECK_REQ = 0x0007,
    GH_PT_ALIVE_CHECK_RES = 0x0008,

    GH_PT_DOIP_ENTITY_STATUS_REQ = 0x4001,
    GH_PT_DOIP_ENTITY_STATUS_RES = 0x4002,
    GH_PT_DIAG_POWER_MODE_INFO_REQ = 0x4003,
    GH_PT_DIAG_POWER_MODE_INFO_RES = 0x4004,

    GH_PT_DIAG_MESSAGE = 0x8001,
    GH_PT_DIAG_MESSAGE_ACK = 0x8002,
    GH_PT_DIAG_MESSAGE_NACK = 0x8003,

    GH_PT_RESERVED = 0xFFFF
};

enum class generic_nack_code_e : uint8_t {
    GH_NACK_INCORRECT_PATTERN_FORMAT = 0x00,            // close socket
    GH_NACK_UNKOWN_PAYLOAD_TYPE = 0x01,                 // discard DoIP message
    GH_NACK_MESSAGE_TOO_LARGE = 0x02,                   // discard DoIP message
    GH_NACK_OUT_OF_MEMORY = 0x03,                       // discard DoIP message
    GH_NACK_INVALID_PAYLOAD_LENGTH = 0x04,              // close socket

    GH_NACK_RESERVED = 0xFF
};

} // namespace fdoip_v1

#endif // FDOIP_V1_ENUMERATION_TYPES_HPP_