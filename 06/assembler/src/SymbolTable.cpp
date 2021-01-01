#include "SymbolTable.hpp"

SymbolTable::SymbolTable()
{
    this->table.clear();
}

SymbolTable::~SymbolTable()
{
}

void SymbolTable::addEntry(std::string symbol, uint32_t address)
{
    this->table.insert({symbol, address});
}

bool SymbolTable::contains(std::string symbol)
{
    auto result = this->table.find(symbol);

    if (result != this->table.end()) {
        return true;
    }

    return false;
}

uint32_t SymbolTable::getAddress(std::string symbol)
{
    return this->table[symbol];
}

