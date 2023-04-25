#pragma once
#include <Storage.h>
using namespace std;
#include <fstream>
#include <iomanip>

class Instruction {
   protected:
    uint32_t bits;
    uint32_t address{};
    string label{};

    explicit Instruction(uint32_t bits);

    string addressString() const;

    virtual string instructionString() const = 0;

   public:
    virtual void toString(ostream& out) const;

    virtual ~Instruction();

    void setAddress(uint32_t givenAddress);
    void setLabel(string givenLabel);
    virtual bool needLabel() const {
        return false;
    }
    virtual uint32_t getImmAddr() const {
        return 0;
    }

    static uint8_t parseOpcodeBits(uint32_t bits);

    static uint8_t parseFunct3(uint32_t bits);

    static uint8_t parseFunct7(uint32_t bits);

    static uint8_t parseRegIndex(uint32_t bits, int startAddress);

    static string parseRd(uint32_t bits);

    static string parseRs1(uint32_t bits);

    static string parseRs2(uint32_t bits);

    static bool isBitSet(uint32_t bits, int index);

    template <typename T>
    static string toHexString(T number);
};

template <typename T>
string Instruction::toHexString(T number) {
    ostringstream ss;
    ss << setfill('0') << setw(sizeof(T) * 2) << hex << number;
    return ss.str();
}
