#include <Instruction.h>
using namespace std;
class SType : public Instruction {
   private:
    static unordered_map<uint8_t, string> mnemonics;

   public:
    explicit SType(uint32_t bits) : Instruction(bits) {}
    ~SType() override = default;

   private:
    string instructionString() const override {
        return getMnemonic() + '\t' + parseRs2(bits) + ", " + parseImm() + '(' + parseRs1(bits) + ')';
    }

    string parseImm() const {
        int16_t imm = 0;

        for (size_t i = 0; i < 5; i++) {
            imm += isBitSet(bits, i + 7) ? (1 << i) : 0;
        }

        for (size_t i = 0; i < 6; i++) {
            imm += isBitSet(bits, i + 25) ? (1 << (i + 5)) : 0;
        }

        imm -= (bits & (1 << (25 + 6))) > 0 ? (1 << 11) : 0;

        return to_string(imm);
    }

    string getMnemonic() const {
        return mnemonics[parseFunct3(bits)];
    }
};
