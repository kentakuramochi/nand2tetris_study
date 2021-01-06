#include <iostream>
#include <string>

#include "Parser.hpp"
#include "Code.hpp"
//#include "SymbolTable.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "error: HACK assembler src file (*.asm) is required" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    Parser parser(argv[1]);
    Code code;

    uint16_t val;

    while (parser.hasMoreCommands()) {
        parser.advance();

        if (parser.commandType() == COMMANDTYPE::A_COMMAND) {
            // A commend
            val = (std::strtoul(parser.symbol().c_str(), nullptr, 10) & 0x7fff);
        } else if (parser.commandType() == COMMANDTYPE::C_COMMAND) {
            // C command
            val = (0xe << 12) |
                  (code.dest(parser.dest()) << 6) |
                  (code.comp(parser.comp()) << 3) |
                  (code.jump(parser.jump()));
        } else {
            // Label
        }

        std::cout << "0x" << std::hex << val << std::endl;
    }

    return EXIT_SUCCESS;
}
