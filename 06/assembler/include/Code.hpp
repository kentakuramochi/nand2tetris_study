#ifndef CODE_HPP
#define CODE_HPP

#include <string>
#include <cstdint>

class Code {
private:

public:
    Code();

    ~Code();

    uint8_t dest(std::string mnemonic);

    uint8_t comp(std::string mnemonic);

    uint8_t jump(std::string mnemonic);
};

#endif

