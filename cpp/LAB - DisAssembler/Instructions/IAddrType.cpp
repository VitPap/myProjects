#include "IAddrType.h"
using namespace std;
// [funct3 | opcode[6]]
unordered_map<uint8_t, string> IAddrType::mnemonics{
    {0b0001, "jalr"},
    {0b0000, "lb"},
    {0b0010, "lh"},
    {0b0100, "lw"},
    {0b1000, "lbu"},
    {0b1010, "lhu"},
};