#include <iostream>
#include <string>
#include <bitset>

#include "Parser.hpp"
#include "Code.hpp"
#include "SymbolTable.hpp"

static bool isDigit(std::string str)
{
    return (str.find_first_not_of("0123456789") == std::string::npos);
}

static std::bitset<16> getACommand(uint16_t value)
{
    return std::bitset<16>(value & 0x7fff);
}

static std::bitset<16> getCCommand(uint8_t comp, uint8_t dest, uint8_t jump)
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

    // open input stream
    std::ifstream ifs(in_file);
    if (!ifs) {
        std::cerr << "error: failed to open \"" << in_file << "\"" << std::endl;
        ifs.close();
        std::exit(EXIT_FAILURE);
    }

    Parser      parser(ifs);
    SymbolTable symbolTable;

    // first scan: regiser labels and addresses
    uint16_t    labelAddress = 0;
    std::string label;
    while (parser.hasMoreCommands()) {
        parser.advance();

        if ((parser.commandType() == COMMANDTYPE::A_COMMAND) ||
            (parser.commandType() == COMMANDTYPE::C_COMMAND)) {
            labelAddress++;
        }

        if (parser.commandType() == COMMANDTYPE::L_COMMAND) {
            label = parser.symbol();
            symbolTable.addEntry(label, labelAddress);
        }
    }

    // reopen for second scan
    ifs.close();
    ifs.open(in_file);

    // open output stream
    auto out_file = in_file.substr(0, in_file.find(".asm")) + ".hack";
    std::ofstream ofs(out_file);
    if (!ofs) {
        std::cerr << "error: failed to open \"" << out_file << "\"" << std::endl;
        ifs.close();
        ofs.close();
        std::exit(EXIT_FAILURE);
    }

    // second scan: parsing assembly source
    Code code;
    std::bitset<16> binCode;
    // address for variable
    uint16_t varAddress = 16;
    while (parser.hasMoreCommands()) {
        parser.advance();

        if (parser.commandType() == COMMANDTYPE::A_COMMAND) {
            // A commend
            auto symbol = parser.symbol();

            if (isDigit(symbol)) {
                // if the symbol is a number, parse as A command
                auto value = static_cast<uint16_t>(std::strtoul(symbol.c_str(), nullptr, 10));
                binCode = getACommand(value);
            } else {
                // otherwise
                if (symbolTable.contains(symbol)) {
                    // if the symbol has already checked, set its address
                    binCode = getACommand(symbolTable.getAddress(symbol));
                } else {
                    // otherwise
                    // register the symbol and address
                    symbolTable.addEntry(symbol, varAddress);
                    binCode = getACommand(varAddress);
                    varAddress++;
                }
            }

            ofs << binCode << std::endl;
        } else if (parser.commandType() == COMMANDTYPE::C_COMMAND) {
            // C command
            binCode = getCCommand(code.comp(parser.comp()),
                                  code.dest(parser.dest()),
                                  code.jump(parser.jump()));

            ofs << binCode << std::endl;
        }
    }

    ifs.close();
    ofs.close();

    return EXIT_SUCCESS;
}
