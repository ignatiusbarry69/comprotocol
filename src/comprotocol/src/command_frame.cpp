#include "comprotocol/command_frame.h"
#include "comprotocol/protocol_error.h"

namespace comprotocol {

CommandFrame::CommandFrame(uint8_t cla, uint8_t ins, uint8_t p1, uint8_t p2, 
                         const std::vector<uint8_t>& data)
    : cla_(cla), ins_(ins), p1_(p1), p2_(p2), data_(data) {}

std::vector<uint8_t> CommandFrame::serializeContent() const {
    std::vector<uint8_t> result;
    result.reserve(5 + data_.size());
    
    result.push_back(cla_);
    result.push_back(ins_);
    result.push_back(p1_);
    result.push_back(p2_);
    result.push_back(static_cast<uint8_t>(data_.size()));  // P3
    result.insert(result.end(), data_.begin(), data_.end());
    
    return result;
}

void CommandFrame::deserializeContent(const std::vector<uint8_t>& data) {
    if (data.size() < 5) {
        throw ProtocolError("Command frame too short");
    }
    
    cla_ = data[0];
    ins_ = data[1];
    p1_ = data[2];
    p2_ = data[3];
    uint8_t p3 = data[4];
    
    if (data.size() != p3 + 5) {
        throw ProtocolError("Command data length mismatch");
    }
    
    data_.assign(data.begin() + 5, data.end());
}

} // namespace comprotocol
