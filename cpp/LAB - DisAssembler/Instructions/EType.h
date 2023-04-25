#pragma once
#include <Instruction.h>
using namespace std;
class EType : public Instruction {
   public:
    explicit EType(uint32_t bits) : Instruction(bits) {}
    ~EType() override = default;

   private:
    string instructionString() const override {
        return getMnemonic() + "\t\t";
    }

    string getMnemonic() const {
        if ((bits >> 20) == 0) {
            return "ecall";
        } else if ((bits >> 20) == 1) {
            return "ebreak";
        } else {
            return "unknown EType";
        }
    }
};