#include "SymbolTable.hpp"

SymbolTable::SymbolTable()
{
    // utility symbols
    this->table_["SP"]   = 0;
    this->table_["LCL"]  = 1;
    this->table_["ARG"]  = 2;
    this->table_["THIS"] = 3;
    this->table_["THAT"] = 4;
    // registers
    this->table_["R0"]  = 0;
    this->table_["R1"]  = 1;
    this->table_["R2"]  = 2;
    this->table_["R3"]  = 3;
    this->table_["R4"]  = 4;
    this->table_["R5"]  = 5;
    this->table_["R6"]  = 6;
    this->table_["R7"]  = 7;
    this->table_["R8"]  = 8;
    this->table_["R9"]  = 9;
    this->table_["R10"] = 10;
    this->table_["R11"] = 11;
    this->table_["R12"] = 12;
    this->table_["R13"] = 13;
    this->table_["R14"] = 14;
    this->table_["R15"] = 15;
    // I/O device
    this->table_["SCREEN"] = 16384;
    this->table_["KBD"]    = 24576;
}

void SymbolTable::addEntry(std::string symbol, uint16_t address)
{
    this->table_[symbol] = address;
}

bool SymbolTable::contains(std::string symbol)
{
    return (this->table_.find(symbol) == this->table_.end()) ? false : true;
}

uint16_t SymbolTable::getAddress(std::string symbol)
{
    return this->table_[symbol];
}
