#include <iostream>
#include <string>
#include <bitset>

#include "Parser.hpp"
#include "Code.hpp"
//#include "SymbolTable.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "error: HACK assembler src file (*.asm) is required" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::string in_file(argv[1]);
    auto pos_ext = in_file.find(".asm");

    if (pos_ext == std::string::npos) {
        std::cerr << "error: HACK assembler src file (*.asm) is required" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    Parser parser(in_file);
    Code code;

    auto out_file = in_file.substr(0, in_file.find(".asm")) + ".hack";
    std::ofstream ofs(out_file);

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

        ofs << std::bitset<16>(val) << std::endl;
    }

    ofs.close();

    return EXIT_SUCCESS;
}
