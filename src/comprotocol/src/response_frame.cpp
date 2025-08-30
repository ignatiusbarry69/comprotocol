#include "comprotocol/response_frame.h"
#include "comprotocol/protocol_error.h"

namespace comprotocol {

ResponseFrame::ResponseFrame(const std::vector<uint8_t>& data, uint16_t sw)
    : data_(data), sw_(sw) {}

std::vector<uint8_t> ResponseFrame::serializeContent() const {
    std::vector<uint8_t> result;
    result.reserve(data_.size() + 2);
    
    result.insert(result.end(), data_.begin(), data_.end());
    result.push_back(static_cast<uint8_t>((sw_ >> 8) & 0xFF));  // SW1
    result.push_back(static_cast<uint8_t>(sw_ & 0xFF));         // SW2
    
    return result;
}

void ResponseFrame::deserializeContent(const std::vector<uint8_t>& data) {
    if (data.size() < 2) {
        throw ProtocolError("Response frame too short");
    }
    
    data_.assign(data.begin(), data.end() - 2);
    sw_ = (static_cast<uint16_t>(data[data.size() - 2]) << 8) | 
           static_cast<uint16_t>(data[data.size() - 1]);
}

std::vector<TLLV> ResponseFrame::parseTLLVs() const {
    std::vector<TLLV> result;
    size_t offset = 0;
    
    while (offset < data_.size()) {
        if (offset + 3 >= data_.size()) {
            throw ProtocolError("Incomplete TLLV structure");
        }
        
        uint16_t len = (static_cast<uint16_t>(data_[offset + 1]) << 8) | 
                       static_cast<uint16_t>(data_[offset + 2]);
                       
        if (offset + 3 + len > data_.size()) {
            throw ProtocolError("TLLV value exceeds data bounds");
        }
        
        TLLV tllv;
        std::vector<uint8_t> tllv_data(data_.begin() + offset, 
                                      data_.begin() + offset + 3 + len);
        tllv.deserialize(tllv_data);
        result.push_back(tllv);
        
        offset += 3 + len;
    }
    
    return result;
}

std::vector<TLV> ResponseFrame::parseTLVs() const {
    std::vector<TLV> result;
    size_t offset = 0;
    
    while (offset < data_.size()) {
        if (offset + 2 >= data_.size()) {
            throw ProtocolError("Incomplete TLV structure");
        }
        
        uint8_t len = data_[offset + 1];
                       
        if (offset + 2 + len > data_.size()) {
            throw ProtocolError("TLV value exceeds data bounds");
        }
        
        TLV tlv;
        std::vector<uint8_t> tlv_data(data_.begin() + offset, 
                                     data_.begin() + offset + 2 + len);
        tlv.deserialize(tlv_data);
        result.push_back(tlv);
        
        offset += 2 + len;
    }
    
    return result;
}

} // namespace comprotocol
