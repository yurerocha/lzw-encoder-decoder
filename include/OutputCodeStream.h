#ifndef OUTPUT_CODE_STREAM_H
#define OUTPUT_CODE_STREAM_H

#include <fstream>

class OutputCodeStream {
public :
    OutputCodeStream(std::ostream &out, unsigned int codeSize) 
        : output( out ),
          pendingBits(0),
          pendingOutput(0),
          codeSize(codeSize)
    { }

    void operator<<(const unsigned int &i) {
        pendingOutput |= i << pendingBits;
        pendingBits += codeSize;
        flush(8);
    }

    void flush() {
        if(pendingBits) {
            output.put(pendingOutput);
        }
    }

private :
    void flush(const int val) {
        while(pendingBits >= val) {
            output.put(pendingOutput & 0xff);
            pendingOutput >>= 8;
            pendingBits -= 8;
        }
    }
    
    std::ostream &output;
    int codeSize;
    int pendingBits;
    unsigned int pendingOutput;
};

#endif