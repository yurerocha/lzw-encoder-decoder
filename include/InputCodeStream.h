#ifndef INPUT_CODE_STREAM_H
#define INPUT_CODE_STREAM_H

#include <fstream>

class InputCodeStream {
public:
    InputCodeStream(std::istream &in, unsigned int codeSize)
        : input(in),
          availableBits(0),
          pendingInput(0),
          codeSize(codeSize)
    { }

    void operator>>(unsigned int &i) {
        while(availableBits < codeSize) {
            char c;
            if(!input.get(c)) {
                return;
            }
            pendingInput |= (c & 0xff) << availableBits;
            availableBits += 8;
        }
        i = pendingInput & ~(~0 << codeSize);
        pendingInput >>= codeSize;
        availableBits -= codeSize;
    }

private:
    std::istream &input;
    int codeSize;
    int availableBits;
    unsigned int pendingInput;
};

#endif