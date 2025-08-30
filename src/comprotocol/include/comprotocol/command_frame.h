#pragma once
#include "frame.h"

namespace comprotocol {

class CommandFrame : public Frame {
public:
    CommandFrame() = default;
    CommandFrame(uint8_t cla, uint8_t ins, uint8_t p1, uint8_t p2, 
                const std::vector<uint8_t>& data = std::vector<uint8_t>());

    uint8_t getCLA() const { return cla_; }
    uint8_t getINS() const { return ins_; }
    uint8_t getP1() const { return p1_; }
    uint8_t getP2() const { return p2_; }
    uint8_t getP3() const { return static_cast<uint8_t>(data_.size()); }
    const std::vector<uint8_t>& getData() const { return data_; }

protected:
    std::vector<uint8_t> serializeContent() const override;
    void deserializeContent(const std::vector<uint8_t>& data) override;

private:
    uint8_t cla_;
    uint8_t ins_;
    uint8_t p1_;
    uint8_t p2_;
    std::vector<uint8_t> data_;
};

} // namespace comprotocol
