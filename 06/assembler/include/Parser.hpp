#ifndef PARSER_H
#define PARSER_H

#include <string>
//#include <ifstream>
#include <fstream>

enum class COMMANDTYPE
{
    A_COMMAND,
    C_COMMAND,
    L_COMMAND
};

class Parser
{
private:
    std::ifstream&  ifs_;
    std::string     currentLine_;
    COMMANDTYPE     type_;
    std::string     symbol_;
    std::string     dest_;
    std::string     comp_;
    std::string     jump_;

public:
    Parser(std::ifstream& ifs) :
        ifs_(ifs) {}

    ~Parser() { this->ifs_.close(); }

    bool hasMoreCommands();

    void advance();

    COMMANDTYPE commandType() { return this->type_; }

    std::string symbol() { return this->symbol_; }
    std::string dest()   { return this->dest_; }
    std::string comp()   { return this->comp_; }
    std::string jump()   { return this->jump_; }
};

#endif
