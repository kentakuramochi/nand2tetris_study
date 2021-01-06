#include "Code.hpp"

Code::Code()
{
}

Code::~Code()
{
}

uint8_t Code::dest(const std::string mnemonic)
{
    uint8_t ret = 0x0;

    if (mnemonic.empty()) {
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
    if (mnemonic.empty()) {
        return 0x0;
    }

    if (mnemonic.compare("0")) {
        // 010 1010
        return 0x2a;
    } else if (mnemonic.compare("1")) {
        // 011 1111
        return 0x3f;
    } else if (mnemonic.compare("-1")) {
        // 011 1010
        return 0x3a;
    } else if (mnemonic.compare("D")) {
        // 000 1100
        return 0x0c;
    } else if (mnemonic.compare("A")) {
        // 011 0000
        return 0x30;
    } else if (mnemonic.compare("M")) {
        // 111 0000
        return 0x70;
    } else if (mnemonic.compare("!D")) {
        // 000 1101
        return 0x0d;
    } else if (mnemonic.compare("!A")) {
        // 011 0001
        return 0x31;
    } else if (mnemonic.compare("!M")) {
        // 111 0001
        return 0x71;
    } else if (mnemonic.compare("-D")) {
        // 000 1111
        return 0x0f;
    } else if (mnemonic.compare("-A")) {
        // 011 0011
        return 0x33;
    } else if (mnemonic.compare("-M")) {
        // 111 0011
        return 0x73;
    } else if (mnemonic.compare("D+1")) {
        // 000 1111
        return 0x0f;
    } else if (mnemonic.compare("A+1)")) {
        // 011 0011
        return 0x33;
    } else if (mnemonic.compare("M+1")) {
        // 111 0011
        return 0x73;
    } else {
        return 0x00;
    }

    return 0;
}

uint8_t Code::jump(const std::string mnemonic)
{
    if (mnemonic.empty()) {
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
        return 0x1;
    }

    // "JMP"
    return 0x7;

    return 0;
}
