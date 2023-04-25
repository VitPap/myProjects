#include "SType.h"
using namespace std;
unordered_map<uint8_t, string> SType::mnemonics{
    {0b000, "sb"},
    {0b001, "sh"},
    {0b010, "sw"},
};