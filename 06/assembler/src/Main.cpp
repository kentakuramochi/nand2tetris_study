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

    while (parser.hasMoreCommands()) {
        // under implementation
        parser.advance();
        std::cout << ">> " << parser.current() << std::endl;

        if (parser.commandType() == COMMANDTYPE::A_COMMAND) {
            std::cout << "A command: A=" << parser.symbol() << std::endl;
        } else if (parser.commandType() == COMMANDTYPE::C_COMMAND) {
            std::cout << "C command:" <<
            "dest=" << parser.dest() << " cmp=" << parser.comp() << " jmp=" << parser.jump() << std::endl;
        } else if (parser.commandType() == COMMANDTYPE::L_COMMAND) {
            std::cout << "Label \"" << parser.symbol() << "\"" << std::endl;
        }
    }

    return EXIT_SUCCESS;
}

