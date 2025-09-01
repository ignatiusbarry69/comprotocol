#ifndef COMPROTOCOL_C_H
#define COMPROTOCOL_C_H

#ifdef __cplusplus
extern "C" {
#endif

// Parse a command. Returns 0 = success, 1 = error
int parseCommand(const unsigned char* input, int inputLen,
                 unsigned char* cla, unsigned char* ins,
                 unsigned char* p1, unsigned char* p2, unsigned char* p3,
                 unsigned char* data, int* dataLen);

// Parse a response. Returns 0 = success, 1 = error
int parseResponse(const unsigned char* input, int inputLen,
                  unsigned char* sw1sw2,
                  unsigned char* data, int* dataLen);

// Compose a command. Returns 0 = success, 1 = error
int composeCommand(unsigned char cla, unsigned char ins,
                   unsigned char p1, unsigned char p2,
                   const unsigned char* data, int dataLen,
                   unsigned char* output, int* outputLen);

// Compose a response. Returns 0 = success, 1 = error
int composeResponse(const unsigned char* sw1sw2,
                    const unsigned char* data, int dataLen,
                    unsigned char* output, int* outputLen);

#ifdef __cplusplus
}
#endif

#endif // COMPROTOCOL_C_H
