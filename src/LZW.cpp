#include "LZW.h"

LZW::LZW(Data* d_p) : data_p(d_p), nexti(0), maxCodeExceed(false) {
    maxCode = std::pow(2, data_p->getCodeSize2());
}

void LZW::encode() {
    fillEncodeDict();
    std::string w = "", k = "";
    outEnco = {data_p->getCodeSize2()};

    while(true) {
        auto [iseof, ch] = data_p->getNext();
        if(iseof) {
            outEnco.push_back(getIndex(w));
            break;
        }

        formatCh(k, ch); // Ctx += ch.
        if(isInEncoded(w + k)) {
            w = w + k;
        } else {
            outEnco.push_back(getIndex(w));
            addCode(w + k);
            w = k;
        }
    }
}

void LZW::decode() {
    fillDecodeDict();
    outDeco.clear();

    int w;

    auto [iseof, ch] = data_p->getNext();
    if(iseof) {
        return;
    }

    outDeco << getCode(ch);
    w = ch;
    while(true) {
        auto [iseof, ch] = data_p->getNext();
        if(iseof) {
            break;
        }

        if(!isInDecoded(ch)) {
            auto strw = getCode(w);
            strw = strw + strw.substr(0, data_p->getCodeSize10());
            addIndex(strw);
            outDeco << strw;
        } else {
            auto strw = getCode(w) + getCode(ch).substr(0, data_p->getCodeSize10());
            addIndex(strw);
            outDeco << getCode(ch);
        }
        w = ch;
    }
}

void LZW::fillEncodeDict() {
    encoded = {};
    nexti = 0;
    for(int i = 0; i < alphabetLen; ++i) {
        std::string ctx = "";
        formatCh(ctx, i);
        addCode(ctx);
    }
}

void LZW::fillDecodeDict() {
    decoded = {};
    nexti = 0;
    for(int i = 0; i < alphabetLen; ++i) {
        std::string ctx = "";
        formatCh(ctx, i);
        addIndex(ctx);
    }
}

void LZW::saveEncoded() {
    auto newfp = data_p->getFilepath().substr(0, data_p->getFilepath().find_last_of(".")); // Rm ".<txt>"
    newfp +=  "_k" + std::to_string(data_p->getCodeSize2());
    std::ofstream f(newfp + ".lzw", std::ios::binary);
    OutputCodeStream os(f, data_p->getCodeSize2());

    auto k = std::to_string(outEnco[0]); // The code size (k) need to be saved in binary.
    f.write(k.c_str(), k.size()); // If saved with "f << outEnco[0]", an extra "\n" is added.
    
    for(auto it = outEnco.begin() + 1; it != outEnco.end(); ++it) {
        os << *it;
    }

    f.close();
}