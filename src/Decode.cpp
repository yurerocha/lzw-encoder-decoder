#include <iostream>
#include <cstdlib>
#include <chrono>
#include "Data.h"
#include "LZW.h"

using namespace std::chrono;

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cout << "Errror: input must be ./" << std::endl;
        return -1;
    }

    std::string fpath = argv[1];

    Data data(fpath);

    std::cout << "Reading input file into buffer" << std::endl;
    data.loadEncodedFile();

    LZW lzw(&data);

    std::cout << "Decoding" << std::endl;
    auto start = high_resolution_clock::now();
    lzw.decode();
    auto stop = high_resolution_clock::now();
    auto et = duration_cast<milliseconds>(stop - start);

    std::cout << "Saving decoded file" << std::endl;
    lzw.saveDecoded();

    auto ts = et.count() / 1000.0;
    std::cout << "Decoding elapsed time: " << ts << " s" << std::endl;
    
    // std::ofstream f("decode.txt", std::ios::app);
    // f << ts << std::endl;
    // f.close();

    return 0;
}