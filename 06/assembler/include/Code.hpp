#ifndef CODE_HPP
#define CODE_HPP

#include <string>
#include <cstdint>

class Code {
private:

public:
    Code() {}

    ~Code() {}

    uint8_t dest(const std::string mnemonic);

    uint8_t comp(const std::string mnemonic);

    uint8_t jump(const std::string mnemonic);
};

#endif
