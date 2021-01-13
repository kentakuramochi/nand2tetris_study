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

bool Parser::hasMoreCommands()
{
    return (this->ifs_.eof()) ? false : true;
}

void Parser::advance()
{
    while (this->hasMoreCommands()) {
        std::getline(this->ifs_, this->currentLine_);

        // remove first space/tab/LF
        while (true) {
            auto pos_sp = this->currentLine_.find_first_of(" \t\r\n");
            if (pos_sp != 0) {
                break;
            }
            this->currentLine_.erase(pos_sp, 1);
        }

        // remove comment area
        auto pos_ds = this->currentLine_.find("//");
        if (pos_ds != std::string::npos) {
            this->currentLine_ = this->currentLine_.substr(0, pos_ds);
        }

        // go next line if empty
        if (this->currentLine_.empty()) {
            continue;
        }

        break;
    }

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
