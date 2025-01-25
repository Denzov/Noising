#ifndef _UI_H_
#define _UI_H_

#include <fstream>
#include <stdint.h>
#include <vector>
#include <iostream>


char* _encoder(char* data, int lenght);
char* _decoder(char* data, int lenght);

typedef char* (*Decoder)(char* data, int lenght);
typedef char* (*Encoder)(char* data, int lenght);

class UI{
private:
    Decoder decoder = _decoder;
    Encoder encoder = _encoder;

    const char* NAME_CONFIG_FILE = "CONFIG";

    bool is_created_CONFIG = 0;
    size_t VALUE_INPUT_PACKET_BITS = 0;
    size_t VALUE_ENCODING_PACKET_BITS = 0;

public: 

    bool pass_bit_values();
    void print();
};

#endif // !_UI_H_