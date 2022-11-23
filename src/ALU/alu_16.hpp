#ifndef _ALU16
#define _ALU16

#include "alu.hpp"
#include <memory>

enum class ALU16Ops { ADD, SUB, MUL, DIV };

class ALU16 : public ALU<uint16_t, ALU16Ops> {
    public:
        uint16_t compute(const uint16_t v1, const uint16_t v2, const ALU16Ops setting) const;

        static ALU16Ops alu_op(uint16_t op_code);
};

#endif
