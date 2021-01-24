#include "Code.hpp"

uint8_t Code::dest(const std::string mnemonic)
{
    uint8_t ret = 0x0;

    if (mnemonic.empty()) {
        // null
        return ret;
    }

    if (mnemonic.find('M') != std::string::npos) {
        ret |= 0x1;
    }
    if (mnemonic.find('D') != std::string::npos) {
        ret |= 0x2;
    }
    if (mnemonic.find('A') != std::string::npos) {
        ret |= 0x4;
    }

    return ret;
}

uint8_t Code::comp(const std::string mnemonic)
{
    if (!mnemonic.compare("1")) {
        // 011 1111
        return 0x3f;
    } else if (!mnemonic.compare("-1")) {
        // 011 1010
        return 0x3a;
    } else if (!mnemonic.compare("D")) {
        // 000 1100
        return 0x0c;
    } else if (!mnemonic.compare("A")) {
        // 011 0000
        return 0x30;
    } else if (!mnemonic.compare("M")) {
        // 111 0000
        return 0x70;
    } else if (!mnemonic.compare("!D")) {
        // 000 1101
        return 0x0d;
    } else if (!mnemonic.compare("!A")) {
        // 011 0001
        return 0x31;
    } else if (!mnemonic.compare("!M")) {
        // 111 0001
        return 0x71;
    } else if (!mnemonic.compare("-D")) {
        // 000 1111
        return 0x0f;
    } else if (!mnemonic.compare("-A")) {
        // 011 0011
        return 0x33;
    } else if (!mnemonic.compare("-M")) {
        // 111 0011
        return 0x73;
    } else if (!mnemonic.compare("D+1")) {
        // 001 1111
        return 0x1f;
    } else if (!mnemonic.compare("A+1")) {
        // 011 0111
        return 0x37;
    } else if (!mnemonic.compare("M+1")) {
        // 111 0111
        return 0x77;
    } else if (!mnemonic.compare("D-1")) {
        // 000 1110
        return 0x0e;
    } else if (!mnemonic.compare("A-1")) {
        // 011 0010
        return 0x32;
    } else if (!mnemonic.compare("M-1")) {
        // 111 0010
        return 0x72;
    } else if (!mnemonic.compare("D+A")) {
        // 000 0010
        return 0x02;
    } else if (!mnemonic.compare("D+M")) {
        // 100 0010
        return 0x42;
    } else if (!mnemonic.compare("D-A")) {
        // 001 0011
        return 0x13;
    } else if (!mnemonic.compare("D-M")) {
        // 101 0011
        return 0x53;
    } else if (!mnemonic.compare("A-D")) {
        // 000 0111
        return 0x07;
    } else if (!mnemonic.compare("M-D")) {
        // 100 0111
        return 0x47;
    } else if (!mnemonic.compare("D&A")) {
        // 000 0000
        return 0x00;
    } else if (!mnemonic.compare("D&M")) {
        // 100 0000
        return 0x40;
    } else if (!mnemonic.compare("D|A")) {
        // 001 0101
        return 0x15;
    } else if (!mnemonic.compare("D|M")) {
        // 101 0101
        return 0x55;
    }

    // "0": 010 1010
    return 0x2a;
}

uint8_t Code::jump(const std::string mnemonic)
{
    if (mnemonic.empty()) {
        // null
        return 0x0;
    }

    if (mnemonic.compare("JGT") == 0) {
        return 0x1;
    } else if (mnemonic.compare("JEQ") == 0) {
        return 0x2;
    } else if (mnemonic.compare("JGE") == 0) {
        return 0x3;
    } else if (mnemonic.compare("JLT") == 0) {
        return 0x4;
    } else if (mnemonic.compare("JNE") == 0) {
        return 0x5;
    } else if (mnemonic.compare("JLE") == 0) {
        return 0x6;
    }

    // "JMP"
    return 0x7;
}
