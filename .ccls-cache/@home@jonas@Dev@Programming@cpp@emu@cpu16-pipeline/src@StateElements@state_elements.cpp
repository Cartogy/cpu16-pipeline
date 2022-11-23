#include "state_elements.hpp"

StateElements::StateElements() {
    clear_registers();
}

void StateElements::clear_registers() {
    for(int i = 0; i < MAX_REGISTERS; i++) {
        registers[i] = 0;
    }
}

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

uint16_t* StateElements::get_register_file() {
    return registers;
}

void StateElements::set_program_counter(size_t pc) {
    program_counter = pc;
}
size_t StateElements::get_program_counter() {
    return program_counter;
}
