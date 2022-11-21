#include "alu_16.hpp"

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
