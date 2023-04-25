#include <Instruction.h>
using namespace std;
class RType : public Instruction {
   private:
    static unordered_map<uint16_t, string> mnemonics;

   public:
    explicit RType(uint32_t bits) : Instruction(bits) {}
    ~RType() override = default;

    string instructionString() const override {
        return getMnemonic() + '\t' + parseRd(bits) + ", " + parseRs1(bits) + ", " + parseRs2(bits);
    }

   private:
    string getMnemonic() const {
        uint16_t key = (parseFunct7(bits) << 3) + parseFunct3(bits);
        return mnemonics[key];
    }
};
