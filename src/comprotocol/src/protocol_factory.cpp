#include "comprotocol/protocol_factory.h"
#include "comprotocol/protocol_error.h"

namespace comprotocol {

std::unique_ptr<CommandFrame> ProtocolFactory::createCommand(
    uint8_t cla, uint8_t ins, uint8_t p1, uint8_t p2, 
    const std::vector<uint8_t>& data) {
    return std::unique_ptr<CommandFrame>(new CommandFrame(cla, ins, p1, p2, data));
}

std::unique_ptr<ResponseFrame> ProtocolFactory::createResponse(
    const std::vector<uint8_t>& data, uint16_t sw) {
    return std::unique_ptr<ResponseFrame>(new ResponseFrame(data, sw));
}

std::unique_ptr<Frame> ProtocolFactory::parseFrame(const std::vector<uint8_t>& data) {
    if (data.size() < 5) {
        throw ProtocolError("Data too short to be a valid frame");
    }
    
    uint16_t len = (static_cast<uint16_t>(data[1]) << 8) | data[2];
    if (len >= 5) {
        uint8_t p3 = data[7];  // 3 (header) + 4 (CLA,INS,P1,P2) + 1 (P3)
        if (len == p3 + 5) {
            std::unique_ptr<CommandFrame> frame(new CommandFrame());
            frame->deserialize(data);
            return frame;
        }
    }
    
    std::unique_ptr<ResponseFrame> frame(new ResponseFrame());
    frame->deserialize(data);
    return frame;
}

} // namespace comprotocol
