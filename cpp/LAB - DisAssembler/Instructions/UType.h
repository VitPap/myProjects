#include <Instruction.h>
using namespace std;
class UType : public Instruction {
   public:
    explicit UType(uint32_t bits) : Instruction(bits) {}
    ~UType() override = default;

   private:
    string instructionString() const override {
        return getMnemonic() + '\t' + parseRd(bits) + ", 0x" + parseImm();
    }

    string parseImm() const {
        int32_t imm = 0;

        for (size_t i = 12; i < 32; i++) {
            imm += isBitSet(bits, i) ? (1 << i) : 0;
        }

        const string s = toHexString(imm);
        return s.substr(0, s.length() - 3);
    }

    string getMnemonic() const {
        const uint8_t opcode = parseOpcodeBits(bits);
        if (opcode == 0b0110111) {
            return "lui";
        } else if (opcode == 0b0010111) {
            return "auipc";
        } else {
            throw runtime_error("Opcode '" + to_string(opcode) + "' doesn't match UType instruction");
        }
    }
};