#include <iostream>
#include <cstdlib>
#include <chrono>
#include "Data.h"
#include "LZW.h"

using namespace std::chrono;

int main(int argc, char* argv[]) {
    if(argc != 3) {
        std::cout << "Errror: input must be ./lzw input code_size" << std::endl;
        return -1;
    }

    std::string fname = argv[1];
    int k = atoi(argv[2]);

    Data data(fname);
    data.setCodeSize(k);
    LZW lzw(&data);

    std::cout << "Reading input file into buffer" << std::endl;
    data.loadFile();

    std::cout << "Encoding" << std::endl;
    auto start = high_resolution_clock::now();
    lzw.encode();
    auto stop = high_resolution_clock::now();
    auto et = duration_cast<milliseconds>(stop - start);

    std::cout << "Saving encoded file" << std::endl;
    lzw.saveEncoded();

    auto ts = et.count() / 1000.0;
    std::cout << "Encoding elapsed time: " << ts << " s" << std::endl;

    // std::ofstream f("encode.txt", std::ios::app);
    // f << lzw.getMaxCodeExceed() << " " << ts << std::endl;
    // f.close();

    return 0;
}