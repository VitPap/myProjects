#include <Instruction.h>
using namespace std;
class IType : public Instruction {
   private:
    bool isShamt;
    static unordered_map<uint8_t, string> mnemonics;

   public:
    IType(uint32_t bits) : Instruction(bits) {
        uint8_t funct3 = parseFunct3(bits);
        isShamt = funct3 == 0b001 || funct3 == 0b101;
    }
    ~IType() = default;

    string instructionString() const override {
        return getMnemonic() + '\t' + parseRd(bits) + ", " + parseRs1(bits) + ", " + parseImm12();
    }

   private:
    string parseImm12() const {
        int16_t imm12 = 0;
        for (size_t i = 0; i < 11; i++) {
            imm12 += isBitSet(bits, i + 20) > 0 ? (1 << i) : 0;
        }

        imm12 -= isBitSet(bits, 11 + 20) > 0 ? (1 << 11) : 0;

        return to_string(imm12);
    }

    string getMnemonic() const {
        uint8_t key = parseFunct3(bits);
        if (isShamt) {
            key += isBitSet(parseFunct7(bits), 5) ? 0b1000 : 0;
        }

        return mnemonics[key];
    }
};
