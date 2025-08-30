#pragma once
#include <vector>
#include <cstdint>

namespace comprotocol {

class TLLV {
public:
    TLLV() = default;
    TLLV(uint8_t tag, const std::vector<uint8_t>& value);

    uint8_t getTag() const { return tag_; }
    const std::vector<uint8_t>& getValue() const { return value_; }
    
    std::vector<uint8_t> serialize() const;
    void deserialize(const std::vector<uint8_t>& data);

private:
    uint8_t tag_;
    std::vector<uint8_t> value_;
};

} // namespace comprotocol
