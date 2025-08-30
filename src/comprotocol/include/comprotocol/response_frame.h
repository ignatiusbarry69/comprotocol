#pragma once
#include "frame.h"
#include "tllv.h"
#include "tlv.h"
#include <vector>

namespace comprotocol {

class ResponseFrame : public Frame {
public:
    ResponseFrame() = default;
    ResponseFrame(const std::vector<uint8_t>& data, uint16_t sw);

    uint16_t getSW() const { return sw_; }
    const std::vector<uint8_t>& getData() const { return data_; }
    
    // Helper methods to parse TLV/TLLV data
    std::vector<TLLV> parseTLLVs() const;
    std::vector<TLV> parseTLVs() const;

protected:
    std::vector<uint8_t> serializeContent() const override;
    void deserializeContent(const std::vector<uint8_t>& data) override;

private:
    std::vector<uint8_t> data_;
    uint16_t sw_;  // Status Word (SW1|SW2)
};

} // namespace comprotocol
