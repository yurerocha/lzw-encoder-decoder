#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <vector>
#include <utility>
#include <sstream>
#include <cmath>
#include "InputCodeStream.h"

#define OFFSET 128

class Data {
public:
    Data(const std::string& fpath) : filepath(fpath), buffer({}), bufferPos(0) { 
        setCodeSize(16); // Code size of 2 bytes.
    }
    
    void loadFile();
    void loadEncodedFile();

    void saveFile(std::stringstream& buffer);
    
    auto getNext() {
        bool iseof = (bufferPos >= buffer.size());
        return std::make_pair(iseof, buffer[bufferPos++]);
    }

    auto getFilepath() { return filepath; }

    int getCodeSize2() { return codeSize2; }
    int getCodeSize10() { return codeSize10; }

    void setCodeSize(int k) {
        codeSize2 = k;
        codeSize10 = std::ceil(std::log10(std::pow(2, k)));
    }

private:
    std::string filepath;
    std::vector<int> buffer;
    int bufferPos;
    int codeSize2;
    int codeSize10;
};

#endif