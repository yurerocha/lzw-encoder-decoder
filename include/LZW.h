#ifndef LZW_H
#define LZW_H

#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "Data.h"
#include "OutputCodeStream.h"

#define STR_SYMB_LEN 3

class LZW {
public:
    LZW(Data* d_p);

    void encode();
    void decode();

    // Used by the encode method.
    int getIndex(const std::string& cd) { return encoded[cd]; } // No bound checking.
    void addCode(const std::string& cd){
        if(encoded.size() < maxCode) {
            encoded[cd] = nexti++;
        } else
            maxCodeExceed = true;
    }
    bool isInEncoded(const std::string& value) {
        return (encoded.find(value) != encoded.end());
    }

    // Used by the decode method.
    std::string getCode(int index) { return decoded[index]; }
    auto addIndex(const std::string& cd) {
        if(decoded.size() < maxCode) {
            decoded[nexti++] = cd;
        }
    }
    bool isInDecoded(int index) {
        return (decoded.find(index) != decoded.end());
    }

    void formatCh(std::string& w, int ch) {
        std::stringstream ss;
        // ss << std::setw(STR_SYMB_LEN) << std::setfill('0') << ch;
        ss << std::setw(data_p->getCodeSize10()) << std::setfill('0') << ch;
        w = ss.str();
    }

    void fillEncodeDict();
    void fillDecodeDict();

    void saveEncoded();
    void saveDecoded() {
        data_p->saveFile(outDeco);
    };

    int getMaxCode() { return maxCode; }
    bool getMaxCodeExceed() { return maxCodeExceed; }

private:

    Data* data_p;
    int maxCode; // Maximum dictionary index.
    std::unordered_map<std::string, int> encoded;
    std::unordered_map<int, std::string> decoded;

    unsigned int nexti;
    const unsigned int alphabetLen = 256; // A = {0, 1, ..., 255}

    std::vector<int> outEnco;
    std::stringstream outDeco;

    bool maxCodeExceed;
};

#endif