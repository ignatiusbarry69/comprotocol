#pragma once
#include <stdexcept>
#include <string>

namespace comprotocol {

class ProtocolError : public std::runtime_error {
public:
    explicit ProtocolError(const std::string& message) : std::runtime_error(message) {}
};

} // namespace comprotocol
