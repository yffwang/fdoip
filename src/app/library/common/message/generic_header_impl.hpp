#ifndef FDOIP_V1_GENERIC_HEADER_IMPL_HPP
#define FDOIP_V1_GENERIC_HEADER_IMPL_HPP

#include <vsomeip/enumeration_types.hpp>
#include <vsomeip/internal/serializable.hpp>

namespace fdoip_v1 {

// class message_base;

class generic_header_impl {
public:
    generic_header_impl();
    generic_header_impl(const generic_header_impl& _header);

public:
    protocol_version_t protocol_version_;
    inverse_protocol_version_t inverse_protocol_version_;
    payload_type_t payload_type_;
    payload_length_t payload_length_;
};

} // namespace fdoip_v1

#endif // FDOIP_V1_GENERIC_HEADER_IMPL_HPP
