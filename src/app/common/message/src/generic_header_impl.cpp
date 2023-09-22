#include "generic_header_impl.hpp"

namespace fdoip_v1 {

generic_header_impl::generic_header_impl()
    : protocol_version_(0x03),
      inverse_protocol_version_(0xFC),
      payload_type_(payload_type_e::GH_PT_RESERVED),
      payload_length_(generic_nack_code_e::GH_NACK_RESERVED) {
}

generic_header_impl::generic_header_impl(const generic_header_impl &_header)
    : protocol_version_(_header.protocol_version_),
      inverse_protocol_version_(_header.inverse_protocol_version_),
      payload_type_(_header.payload_type_),
      payload_length_(_header.payload_length_) {
}

} // namespace fdoip_v1
