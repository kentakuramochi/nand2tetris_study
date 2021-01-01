#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <string>
#include <unordered_map>

class SymbolTable
{
private:
    std::unordered_map<std::string, uint32_t> table;

public:
    SymbolTable();

    ~SymbolTable();

    void addEntry(std::string symbol, uint32_t address);

    bool contains(std::string symbol);

    uint32_t getAddress(std::string symbol);
};

#endif

