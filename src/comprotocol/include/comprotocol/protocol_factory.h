#pragma once
#include "frame.h"
#include "command_frame.h"
#include "response_frame.h"
#include <memory>

namespace comprotocol {

class ProtocolFactory {
public:
    static std::unique_ptr<CommandFrame> createCommand(uint8_t cla, uint8_t ins, 
                                                     uint8_t p1, uint8_t p2,
                                                     const std::vector<uint8_t>& data = std::vector<uint8_t>());
    
    static std::unique_ptr<ResponseFrame> createResponse(const std::vector<uint8_t>& data, 
                                                       uint16_t sw);
                                                       
    static std::unique_ptr<Frame> parseFrame(const std::vector<uint8_t>& data);
    
    static std::unique_ptr<CommandFrame> parseCommand(const std::vector<uint8_t>& data);
    
    static std::unique_ptr<ResponseFrame> parseResponse(const std::vector<uint8_t>& data);
};

} // namespace comprotocol
