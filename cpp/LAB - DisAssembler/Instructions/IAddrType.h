#include <Instruction.h>
using namespace std;
class IAddrType : public Instruction {
   private:
    static unordered_map<uint8_t, string> mnemonics;

   public:
    explicit IAddrType(uint32_t bits) : Instruction(bits) {}
    ~IAddrType() override = default;

    string instructionString() const override {
        return getMnemonic() + '\t' + parseRd(bits) + ", " + parseImm12() + '(' + parseRs1(bits) + ')';
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
        uint8_t key = (parseFunct3(bits) << 1) + (isBitSet(bits, 6) ? 1 : 0);
        return mnemonics[key];
    }
};
