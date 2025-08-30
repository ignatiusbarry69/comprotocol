#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdint>
#include "comprotocol.h"

void printHex(const std::vector<uint8_t>& data) {
    for (uint8_t byte : data) {
        std::cout << std::hex << std::uppercase << std::setw(2) 
                  << std::setfill('0') << static_cast<int>(byte) << " ";
    }
    std::cout << std::dec << std::endl;
}

void testTLLV() {
    std::cout << "\nTesting TLLV:" << std::endl;
    comprotocol::TLLV tllv(0x01, {0x11, 0x22, 0x33});
    auto tlvData = tllv.serialize();
    std::cout << "TLLV data: ";
    printHex(tlvData);
}

void testTLV() {
    std::cout << "\nTesting TLV:" << std::endl;
    comprotocol::TLV tlv(0x02, {0x44, 0x55});
    auto tlvData = tlv.serialize();
    std::cout << "TLV data: ";
    printHex(tlvData);
}

int main() {
    try {
        // Test basic TLLV and TLV functionality
        auto version = comprotocol::version();
        std::cout << "Comprotocol version: " << version << std::endl;
        
        testTLLV();
        testTLV();

        // Create a command
        auto command = comprotocol::ProtocolFactory::createCommand(
            0x00,  // CLA
            0x80,  // INS
            0x00,  // P1
            0x00,  // P2
            {}  // Data
        );
        
        // Serialize the command
        auto commandData = command->serialize();
        std::cout << "\nCommand: ";
        printHex(commandData);
        
        // Create a response with both TLLV and TLV
        std::vector<uint8_t> responseData;
        
        // // Add a TLLV
        // comprotocol::TLLV tllv(0x01, {0x11, 0x22, 0x33});
        // auto tllvData = tllv.serialize();
        // responseData.insert(responseData.end(), tllvData.begin(), tllvData.end());
        
        // Add a TLV
        comprotocol::TLV tlv(0x02, {0x44, 0x55});
        auto tlvData = tlv.serialize();
        responseData.insert(responseData.end(), tlvData.begin(), tlvData.end());
        
        auto response = comprotocol::ProtocolFactory::createResponse(
            responseData,  // Combined TLV/TLLV data
            0x9000   // SW
        );
        
        // Serialize the response
        auto serializedResponse = response->serialize();
        std::cout << "Response with both TLV and TLLV: ";
        printHex(serializedResponse);
        
        // Parse the response back
        auto parsedFrame = comprotocol::ProtocolFactory::parseFrame(serializedResponse);
        auto* parsedResponse = dynamic_cast<comprotocol::ResponseFrame*>(parsedFrame.get());
        
        if (parsedResponse) {
            // Parse TLLVs
            // auto tllvs = parsedResponse->parseTLLVs();
            // std::cout << "Parsed TLLV tag: 0x" << std::hex 
            //          << static_cast<int>(tllvs[0].getTag()) << std::endl;
            
            // Parse TLVs
            auto tlvs = parsedResponse->parseTLVs();
            std::cout << "Parsed TLV tag: 0x" << std::hex 
                     << static_cast<int>(tlvs[0].getTag()) << std::endl;
        }
        
        return 0;
    } catch (const comprotocol::ProtocolError& e) {
        std::cerr << "Protocol error: " << e.what() << std::endl;
        return 1;
    }
}
