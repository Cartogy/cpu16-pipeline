#include "state_elements.hpp"

void StateElements::set_instruction(uint16_t ins) {
    current_instruction = ins;
}

uint16_t StateElements::get_current_instruction() {
    return current_instruction;
}
