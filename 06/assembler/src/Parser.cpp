#include "Parser.hpp"

#include <iostream>

static std::string trimComment(std::string str)
{
    auto pos_ds = str.find("//");
    if (pos_ds != std::string::npos) {
        str = str.substr(0, pos_ds);
    }
    return str;
}

static std::string trimSpace(std::string str)
{
    while (true) {
        auto pos_sp = str.find_first_of(" \t\r\n");
        if (pos_sp == std::string::npos) {
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

        // remove space/tab/LF
        this->currentLine_ = trimSpace(this->currentLine_);

        // return true if get command string
        if (!this->currentLine_.empty()) {
            return true;
        }
    }

    return false;
}

static std::string getSymbol(std::string str)
{
    return str.substr(1, (str.length() - 1));
}

static std::string getLabelSymbol(std::string str)
{
    return str.substr(1, (str.length() - 2));
}

static std::string getDest(std::string str, std::string::size_type pos_eq)
{
    return str.substr(0, pos_eq);
}

static std::string getComp(std::string str, std::string::size_type pos_eq, std::string::size_type pos_sc)
{
    std::string::size_type start = (pos_eq == std::string::npos) ? 0 : (pos_eq + 1);
    std::string::size_type end   = (pos_sc == std::string::npos) ? str.length() : pos_sc;

    return str.substr(start, (end - start));
}

static std::string getJump(std::string str, std::string::size_type pos_sc)
{
    return str.substr((pos_sc + 1), (str.length() - pos_sc - 1));
}

void Parser::advance()
{
    this->symbol_ = "";
    this->dest_   = "";
    this->comp_   = "";
    this->jump_   = "";

    // try to parse A command
    auto pos_at = this->currentLine_.find("@");
    if (pos_at != std::string::npos) {
        this->type_   = COMMANDTYPE::A_COMMAND;
        this->symbol_ = getSymbol(this->currentLine_);
        return;
    }

    // try to parse L command
    auto pos_par = this->currentLine_.find("(");
    if (pos_par != std::string::npos) {
        this->type_   = COMMANDTYPE::L_COMMAND;
        this->symbol_ = getLabelSymbol(this->currentLine_);
        return;
    }

    // otherwise
    // C command
    this->type_ = COMMANDTYPE::C_COMMAND;
    auto pos_eq = this->currentLine_.find("=");
    auto pos_sc = this->currentLine_.find(";");
    if ((pos_eq != std::string::npos) && (pos_sc != std::string::npos)) {
        // dest=comp;jmp
        this->dest_ = getDest(this->currentLine_, pos_eq);
        this->comp_ = getComp(this->currentLine_, pos_eq, pos_sc);
        this->jump_ = getJump(this->currentLine_, pos_sc);
    } else if (pos_eq != std::string::npos) {
        // dest=comp
        this->dest_ = getDest(this->currentLine_, pos_eq);
        this->comp_ = getComp(this->currentLine_, pos_eq, pos_sc);
    } else {
        // comp;jmp
        this->comp_ = getComp(this->currentLine_, pos_eq, pos_sc);
        this->jump_ = getJump(this->currentLine_, pos_sc);
    }

    return;
}
