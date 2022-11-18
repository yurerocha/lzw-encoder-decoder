#include "Data.h"

void Data::loadFile() {
    std::ifstream file(filepath, std::ios::binary);

    std::istreambuf_iterator<char> it{file}, end;

    // Get length of file:
    file.seekg (0, file.end);
    int len = file.tellg();
    file.seekg (0, file.beg);

    // Load file data into buffer.
    buffer.reserve(len);
    while(it != end) {
        int ch = OFFSET + *it++;

        buffer.push_back(ch);
    }

    file.close();
}

void Data::loadEncodedFile() {
    buffer = {};
    bufferPos = 0;

    std::ifstream f(filepath);

    unsigned int n;
    f >> n;
    if(f.eof()) {
        return;
    }
    setCodeSize(n);

    InputCodeStream is(f, codeSize2);

    while(true) {
        is >> n;
        // std::cout << n << std::endl;
        // getchar();
        if(f.eof()) {
            break;
        }

        buffer.push_back(n);
    }

    f.close();
}

void Data::saveFile(std::stringstream& buffer) {
    auto newfp = filepath.substr(0, filepath.find_last_of(".")); // Rm ".<lzw>"
    std::ofstream file(newfp, std::ios::binary);

    char ch[codeSize10];
    while(true) {
        buffer.read(ch, codeSize10);
        if(buffer.eof())
            break; 

        int symb = atoi(ch) - OFFSET;
        file << (char)symb;
    }

    file.close();
}