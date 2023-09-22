#ifndef FDOIP_V1_PRIMITIVE_TYPES_HPP_
#define FDOIP_V1_PRIMITIVE_TYPES_HPP_

#include <array>
#include <cstdint>
#include <string>
#include <sys/types.h>

namespace fdoip_v1 {

typedef uint8_t protocol_version_t;
typedef uint8_t inverse_protocol_version_t;
typedef uint16_t payload_type_t;
typedef uint32_t payload_length_t;

typedef std::array<byte_t, 4> ipv4_address_t;
typedef std::array<byte_t, 16> ipv6_address_t;
typedef std::uint16_t port_t;

} // namespace fdoip_v1

#endif // FDOIP_V1_PRIMITIVE_TYPES_HPP_

