#include "comprotocol/frame.h"
#include "comprotocol/protocol_error.h"
#include <numeric>
#include <algorithm>

namespace comprotocol {

std::vector<uint8_t> Frame::serialize() const {
    std::vector<uint8_t> content = serializeContent();
    std::vector<uint8_t> result;
    result.reserve(content.size() + 4);  // STX + LenH + LenL + content + LRC
    
    result.push_back(STX);
    uint16_t len = static_cast<uint16_t>(content.size());
    result.push_back(static_cast<uint8_t>((len >> 8) & 0xFF));  // LenH
    result.push_back(static_cast<uint8_t>(len & 0xFF));         // LenL
    
    result.insert(result.end(), content.begin(), content.end());
    
    // Calculate LRC over length and content
    uint8_t lrc = calculateLRC(std::vector<uint8_t>(result.begin() + 1, result.end()));
    result.push_back(lrc);
    
    return result;
}

void Frame::deserialize(const std::vector<uint8_t>& data) {
    if (data.size() < 5) {  // STX + LenH + LenL + at least 1 byte content + LRC
        throw ProtocolError("Frame too short");
    }
    
    if (data[0] != STX) {
        throw ProtocolError("Invalid STX");
    }
    
    uint16_t len = (static_cast<uint16_t>(data[1]) << 8) | data[2];
    if (data.size() != len + 4) {  // STX + LenH + LenL + content + LRC
        throw ProtocolError("Frame length mismatch");
    }
    
    // Verify LRC
    uint8_t expected_lrc = calculateLRC(std::vector<uint8_t>(data.begin() + 1, data.end() - 1));
    if (expected_lrc != data.back()) {
        throw ProtocolError("LRC verification failed");
    }
    
    // Extract content
    std::vector<uint8_t> content(data.begin() + 3, data.end() - 1);
    deserializeContent(content);
}

uint8_t Frame::calculateLRC(const std::vector<uint8_t>& data) {
    return std::accumulate(data.begin(), data.end(), static_cast<uint8_t>(0), 
                          std::bit_xor<uint8_t>());
}

} // namespace comprotocol
