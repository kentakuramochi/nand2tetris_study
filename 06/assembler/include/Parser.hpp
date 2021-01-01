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
    std::ifstream   ifs;
    std::string     currentLine;
    COMMANDTYPE     cType;
    std::string     cSymbol;
    std::string     cDest;
    std::string     cComp;
    std::string     cJump;

public:
    Parser(std::string asmFile);
    Parser(char* asmFile) :
        Parser(std::string(asmFile)) {};

    ~Parser();

    bool hasMoreCommands();

    void advance();

    COMMANDTYPE commandType() { return this->cType; }

    std::string current() { return this->currentLine; }

    std::string symbol() { return this->cSymbol; }
    std::string dest()   { return this->cDest; }
    std::string comp()   { return this->cComp; }
    std::string jump()   { return this->cJump; }
};

#endif

