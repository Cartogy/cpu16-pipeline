#include "alu_16.hpp"

ALU16Ops ALU16::alu_op(uint16_t op_code) {
    if (op_code >= 0xc) {   // Branches (0xc -> 12)
        return ALU16Ops::SUB;
    } else if (op_code >= 0x8) {    // load/store and immediates
        return ALU16Ops::ADD;
    } else if (op_code >= 0x4) {    // R-Instructions
        if (op_code == 0x4) {
            return ALU16Ops::ADD;
        } else if (op_code == 0x5) {
            return ALU16Ops::SUB;
        } else if (op_code == 0x6) {
            return ALU16Ops::MUL;
        } else {
            return ALU16Ops::DIV;
        }
    } else {    // J-Instructions
        return ALU16Ops::ADD;
    }
}

uint16_t ALU16::compute(const uint16_t v1, const uint16_t v2, const ALU16Ops setting) const {
    if (setting == ALU16Ops::ADD) {
        return v1 + v2;
    } else if (setting == ALU16Ops::SUB) {
        return v1 - v2;
    } else if (setting == ALU16Ops::MUL) {
        return v1 * v2;
    } else {
        return v1 / v2;
    }
}
