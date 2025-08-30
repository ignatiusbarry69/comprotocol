#include "comprotocol/tlv.h"
#include "comprotocol/protocol_error.h"

namespace comprotocol {

TLV::TLV(uint8_t tag, const std::vector<uint8_t>& value)
    : tag_(tag), value_(value) {
    if (value.size() > 255) {
        throw ProtocolError("TLV value too long for single byte length");
    }
}

std::vector<uint8_t> TLV::serialize() const {
    if (value_.size() > 255) {
        throw ProtocolError("TLV value too long for single byte length");
    }

    std::vector<uint8_t> result;
    result.reserve(2 + value_.size()); // Tag + Len + Value
    
    result.push_back(tag_);
    result.push_back(static_cast<uint8_t>(value_.size())); // Single byte length
    result.insert(result.end(), value_.begin(), value_.end());
    
    return result;
}

void TLV::deserialize(const std::vector<uint8_t>& data) {
    if (data.size() < 2) {
        throw ProtocolError("TLV data too short");
    }
    
    tag_ = data[0];
    uint8_t len = data[1];
    
    if (data.size() < len + 2) {
        throw ProtocolError("TLV value shorter than specified length");
    }
    
    value_.assign(data.begin() + 2, data.begin() + 2 + len);
}

} // namespace comprotocol
