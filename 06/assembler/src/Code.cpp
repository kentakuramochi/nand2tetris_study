#include "Code.hpp"

Code::Code()
{
}

Code::~Code()
{
}

uint8_t Code::dest(std::string mnemonic)
{
    if (mnemonic.empty()) {
        return 1;
    }

    return 0;
}

uint8_t Code::comp(std::string mnemonic)
{
    if (mnemonic.empty()) {
        return 1;
    }

    return 0;
}

uint8_t Code::jump(std::string mnemonic)
{
    if (mnemonic.empty()) {
        return 1;
    }

    return 0;
}

