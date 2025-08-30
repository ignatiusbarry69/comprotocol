#pragma once
#include <vector>
#include <cstdint>

namespace comprotocol {

// Constants
constexpr uint8_t STX = 0x02;

class IFrame {
public:
    virtual ~IFrame() = default;
    virtual std::vector<uint8_t> serialize() const = 0;
    virtual void deserialize(const std::vector<uint8_t>& data) = 0;
};

class Frame : public IFrame {
public:
    Frame() = default;
    virtual ~Frame() = default;

    std::vector<uint8_t> serialize() const override;
    void deserialize(const std::vector<uint8_t>& data) override;

protected:
    virtual std::vector<uint8_t> serializeContent() const = 0;
    virtual void deserializeContent(const std::vector<uint8_t>& data) = 0;
    static uint8_t calculateLRC(const std::vector<uint8_t>& data);
};

} // namespace comprotocol
