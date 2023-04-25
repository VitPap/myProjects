#include <Instruction.h>
using namespace std;
class UnknownType : public Instruction {
   public:
    explicit UnknownType(uint32_t bits) : Instruction(bits) {}
    ~UnknownType() override = default;

   private:
    string instructionString() const override {
        return "unknown_instruction";
    }
};
