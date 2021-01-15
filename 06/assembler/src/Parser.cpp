#include "Parser.hpp"

#include <iostream>

Parser::Parser(std::string asmFile)
{
    this->type_ = COMMANDTYPE::L_COMMAND;
    this->ifs_.open(asmFile);
}

Parser::~Parser()
{
    this->ifs_.close();
}

static std::string trimComment(std::string str) {
    auto pos_ds = str.find("//");
    if (pos_ds != std::string::npos) {
        str = str.substr(0, pos_ds);
    }
    return str;
}

static std::string trimHeadSpace(std::string str) {
    while (true) {
        auto pos_sp = str.find_first_of(" \t\r\n");
        if (pos_sp != 0) {
            break;
        }
        str.erase(pos_sp, 1);
    }

    return str;
}

bool Parser::hasMoreCommands()
{
    while (!this->ifs_.eof()) {
        std::getline(this->ifs_, this->currentLine_);

        // remove comment area
        this->currentLine_ = trimComment(this->currentLine_);

        // remove first space/tab/LF
        this->currentLine_ = trimHeadSpace(this->currentLine_);

        // return true if get command string
        if (!this->currentLine_.empty()) {
            return true;
        }
    }

    return false;
}

void Parser::advance()
{
    this->symbol_ = "";
    this->dest_   = "";
    this->comp_   = "";
    this->jump_   = "";

    // A command
    auto pos_at = this->currentLine_.find("@");
    if (pos_at != std::string::npos) {
        this->type_ = COMMANDTYPE::A_COMMAND;
        this->symbol_ = this->currentLine_.substr((pos_at + 1), (this->currentLine_.length() - 1));
        return;
    }

    // delimiters of C command
    auto pos_eq = this->currentLine_.find("=");
    auto pos_sc = this->currentLine_.find(";");

    // if not delimiters, thought as a label
    if ((pos_eq != std::string::npos) && (pos_sc != std::string::npos)) {
        this->type_ = COMMANDTYPE::L_COMMAND;
        this->symbol_ = this->currentLine_;
    }

    // C command
    this->type_ = COMMANDTYPE::C_COMMAND;

    if ((pos_eq != std::string::npos) && (pos_sc != std::string::npos)) {
        // dest=comp;jmp
        this->dest_ = this->currentLine_.substr(0, pos_eq);
        this->comp_ = this->currentLine_.substr((pos_eq + 1), pos_sc);
        this->jump_ = this->currentLine_.substr((pos_sc + 1), (this->currentLine_.length() - pos_sc - 2));
    } else if (pos_eq != std::string::npos) {
        // dest=comp
        this->dest_ = this->currentLine_.substr(0, pos_eq);
        this->comp_ = this->currentLine_.substr((pos_eq + 1), (this->currentLine_.length() - pos_eq - 2));
    } else {
        // comp;jmp
        this->comp_ = this->currentLine_.substr(0, pos_sc);
        this->jump_ = this->currentLine_.substr((pos_sc + 1), (this->currentLine_.length() - pos_sc - 2));
    }

    return;
}
