#include "comprotocol/tllv.h"
#include "comprotocol/protocol_error.h"

namespace comprotocol {

TLLV::TLLV(uint8_t tag, const std::vector<uint8_t>& value)
    : tag_(tag), value_(value) {}

std::vector<uint8_t> TLLV::serialize() const {
    std::vector<uint8_t> result;
    result.reserve(4 + value_.size());
    
    result.push_back(tag_);
    uint16_t len = static_cast<uint16_t>(value_.size());
    result.push_back(static_cast<uint8_t>((len >> 8) & 0xFF));  // LenH
    result.push_back(static_cast<uint8_t>(len & 0xFF));         // LenL
    result.insert(result.end(), value_.begin(), value_.end());
    
    return result;
}

void TLLV::deserialize(const std::vector<uint8_t>& data) {
    if (data.size() < 4) {
        throw ProtocolError("TLLV data too short");
    }
    
    tag_ = data[0];
    uint16_t len = (static_cast<uint16_t>(data[1]) << 8) | data[2];
    
    if (data.size() < len + 3) {
        throw ProtocolError("TLLV value shorter than specified length");
    }
    
    value_.assign(data.begin() + 3, data.begin() + 3 + len);
}

} // namespace comprotocol
