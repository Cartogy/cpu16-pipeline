#include "state_elements.hpp"

void StateElements::set_instruction(uint16_t ins) {
    current_instruction = ins;
}

uint16_t StateElements::get_current_instruction() {
    return current_instruction;
}

void StateElements::set_register_value(uint16_t reg_index, uint16_t value) {
    registers[reg_index] = value;
}

uint16_t StateElements::get_register_value(uint16_t reg_index) {
    return registers[reg_index];
}

