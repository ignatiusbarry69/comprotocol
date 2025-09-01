#include "comprotocolC.h"
#include "comprotocol/protocol_factory.h"
#include <cstring>
#include <vector>

extern "C" {

int parseCommand(const unsigned char* input, int inputLen,
                 unsigned char* cla, unsigned char* ins,
                 unsigned char* p1, unsigned char* p2, unsigned char* p3,
                 unsigned char* data, int* dataLen) {
    if (!input || inputLen <= 0 || !cla || !ins || !p1 || !p2 || !p3 || !dataLen) {
        return 1;
    }

    try {
        std::vector<uint8_t> inputVec(input, input + inputLen);
        auto command = comprotocol::ProtocolFactory::parseCommand(inputVec);

        *cla = command->getCLA();
        *ins = command->getINS();
        *p1  = command->getP1();
        *p2  = command->getP2();

        const auto& cmdData = command->getData();
        *p3 = static_cast<unsigned char>(cmdData.size());
        *dataLen = static_cast<int>(cmdData.size());

        if (!cmdData.empty() && data) {
            std::memcpy(data, cmdData.data(), cmdData.size());
        }
        return 0;
    } catch (...) {
        return 1;
    }
}

int parseResponse(const unsigned char* input, int inputLen,
                  unsigned char* sw1sw2,
                  unsigned char* data, int* dataLen) {
    if (!input || inputLen <= 0 || !sw1sw2 || !dataLen) {
        return 1;
    }

    try {
        std::vector<uint8_t> inputVec(input, input + inputLen);
        auto response = comprotocol::ProtocolFactory::parseResponse(inputVec);

        uint16_t sw = response->getSW();
        sw1sw2[0] = static_cast<unsigned char>((sw >> 8) & 0xFF);
        sw1sw2[1] = static_cast<unsigned char>(sw & 0xFF);

        const auto& respData = response->getData();
        *dataLen = static_cast<int>(respData.size());

        if (!respData.empty() && data) {
            std::memcpy(data, respData.data(), respData.size());
        }
        return 0;
    } catch (...) {
        return 1;
    }
}

int composeCommand(unsigned char cla, unsigned char ins,
                   unsigned char p1, unsigned char p2,
                   const unsigned char* data, int dataLen,
                   unsigned char* output, int* outputLen) {
    if (!output || !outputLen || (dataLen > 0 && !data)) {
        return 1;
    }

    try {
        std::vector<uint8_t> cmdData;
        if (dataLen > 0) {
            cmdData.assign(data, data + dataLen);
        }

        auto command = comprotocol::ProtocolFactory::createCommand(cla, ins, p1, p2, cmdData);
        std::vector<uint8_t> serialized = command->serialize();

        *outputLen = static_cast<int>(serialized.size());
        std::memcpy(output, serialized.data(), serialized.size());
        return 0;
    } catch (...) {
        return 1;
    }
}

int composeResponse(const unsigned char* sw1sw2,
                    const unsigned char* data, int dataLen,
                    unsigned char* output, int* outputLen) {
    if (!sw1sw2 || !output || !outputLen) {
        return 1;
    }

    try {
        uint16_t sw = (static_cast<uint16_t>(sw1sw2[0]) << 8) |
                       static_cast<uint16_t>(sw1sw2[1]);

        std::vector<uint8_t> respData;
        if (data && dataLen > 0) {
            respData.assign(data, data + dataLen);
        }

        auto response = comprotocol::ProtocolFactory::createResponse(respData, sw);
        std::vector<uint8_t> serialized = response->serialize();

        *outputLen = static_cast<int>(serialized.size());
        std::memcpy(output, serialized.data(), serialized.size());
        return 0;
    } catch (...) {
        return 1;
    }
}

} // extern "C"
