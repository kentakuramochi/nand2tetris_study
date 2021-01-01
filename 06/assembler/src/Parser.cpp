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
    std::getline(this->ifs, this->currentLine);

    std::size_t pos_com;
    do {
        pos_com = this->currentLine.find("//");
    } while (pos_com != std::string::npos);

    auto pos_at = this->currentLine.find("@");
    if (pos_at != std::string::npos) {
        this->cType   = COMMANDTYPE::A_COMMAND;
        this->cSymbol = this->currentLine.substr(1);
        return;
    }

    auto pos_eq = this->currentLine.find("=");
    auto pos_sc = this->currentLine.find(";");
    if ((pos_eq != std::string::npos) || (pos_sc != std::string::npos)) {
        this->cType = COMMANDTYPE::C_COMMAND;

        this->cDest = "";
        this->cComp = "";
        this->cJump = "";

        if ((pos_eq != std::string::npos) && (pos_sc != std::string::npos)) { 
            this->cDest = this->currentLine.substr(0, pos_eq);
            this->cComp = this->currentLine.substr((pos_eq + 1), (pos_sc - pos_eq));
            this->cJump = this->currentLine.substr((pos_sc + 1));
        } else if (pos_eq != std::string::npos) {
            this->cDest = this->currentLine.substr(0, pos_eq);
            this->cComp = this->currentLine.substr((pos_eq + 1));
        } else if (pos_sc != std::string::npos) {
            this->cComp = this->currentLine.substr(0, pos_sc);
            this->cJump = this->currentLine.substr((pos_sc + 1));
        }

        return;
    }

    this->cType = COMMANDTYPE::L_COMMAND;
    this->cSymbol = this->currentLine;

    return;
}
