#include "Parser.hpp"

#include <iostream>

Parser::Parser(std::string asmFile)
{
    this->ifs.open(asmFile);
}

Parser::~Parser()
{
    this->cType = COMMANDTYPE::L_COMMAND;
    this->ifs.close();
}

bool Parser::hasMoreCommands()
{
    return (this->ifs.eof()) ? false : true;
}

void Parser::advance()
{
    while (this->hasMoreCommands()) {
        std::getline(this->ifs, this->currentLine);

        // remove first space/tab/LF
        while (true) {
            auto pos_sp = this->currentLine.find_first_of(" \t\r\n");
            if (pos_sp != 0) {
                break;
            }
            this->currentLine.erase(pos_sp, 1);
        }

        // remove comment area
        auto pos_ds = this->currentLine.find("//");
        if (pos_ds != std::string::npos) {
            this->currentLine = this->currentLine.substr(0, pos_ds);
        }

        // go next line if empty
        if (this->currentLine.empty()) {
            continue;
        }

        break;
    }

    this->cSymbol = "";
    this->cDest   = "";
    this->cComp   = "";
    this->cJump   = "";

    // A command
    auto pos_at = this->currentLine.find("@");
    if (pos_at != std::string::npos) {
        this->cType = COMMANDTYPE::A_COMMAND;
        this->cSymbol = this->currentLine.substr((pos_at + 1), (this->currentLine.length() - 1));
        return;
    }

    // delimiters of C command
    auto pos_eq = this->currentLine.find("=");
    auto pos_sc = this->currentLine.find(";");

    // if not delimiters, thought as a label
    if ((pos_eq != std::string::npos) && (pos_sc != std::string::npos)) {
        this->cType = COMMANDTYPE::L_COMMAND;
        this->cSymbol = this->currentLine;
    }

    // C command
    this->cType = COMMANDTYPE::C_COMMAND;

    if ((pos_eq != std::string::npos) && (pos_sc != std::string::npos)) {
        // dest=comp;jmp
        this->cDest = this->currentLine.substr(0, pos_eq);
        this->cComp = this->currentLine.substr((pos_eq + 1), pos_sc);
        this->cJump = this->currentLine.substr((pos_sc + 1), (this->currentLine.length() - pos_sc - 2));
    } else if (pos_eq != std::string::npos) {
        // dest=comp
        this->cDest = this->currentLine.substr(0, pos_eq);
        this->cComp = this->currentLine.substr((pos_eq + 1), (this->currentLine.length() - pos_eq - 2));
    } else {
        // comp;jmp
        this->cComp = this->currentLine.substr(0, pos_sc);
        this->cJump = this->currentLine.substr((pos_sc + 1), (this->currentLine.length() - pos_sc - 2));
    }

    return;
}
