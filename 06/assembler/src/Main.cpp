#include <iostream>
#include <string>
#include <bitset>

#include "Parser.hpp"
#include "Code.hpp"
//#include "SymbolTable.hpp"

std::bitset<16> getACommand(std::string str)
{
    return std::bitset<16>(std::strtoul(str.c_str(), nullptr, 10) & 0x7fff);
}

std::bitset<16> getCCommand(uint8_t comp, uint8_t dest, uint8_t jump)
{
    return std::bitset<16>((0xe << 12) |
                           (comp << 6) |
                           (dest << 3) |
                           jump);
}

int main(int argc, char *argv[])
{
    // check argument
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

    // open source file
    std::ifstream ifs(in_file);
    if (!ifs) {
        std::cerr << "error: failed to open \"" << in_file << "\"" << std::endl;
        ifs.close();
        std::exit(EXIT_FAILURE);
    }

    Parser parser(ifs);
    Code code;
    std::bitset<16> binCode;

    auto out_file = in_file.substr(0, in_file.find(".asm")) + ".hack";
    std::ofstream ofs(out_file);
    if (!ofs) {
        std::cerr << "error: failed to open \"" << out_file << "\"" << std::endl;
        ifs.close();
        ofs.close();
        std::exit(EXIT_FAILURE);
    }

    while (parser.hasMoreCommands()) {
        parser.advance();

        if (parser.commandType() == COMMANDTYPE::A_COMMAND) {
            // A commend
            binCode = getACommand(parser.symbol());
        } else if (parser.commandType() == COMMANDTYPE::C_COMMAND) {
            // C command
            binCode = getCCommand(code.comp(parser.comp()),
                                  code.dest(parser.dest()),
                                  code.jump(parser.jump()));
        } else {
            // Label
        }

        ofs << binCode << std::endl;
    }

    ifs.close();
    ofs.close();

    return EXIT_SUCCESS;
}
