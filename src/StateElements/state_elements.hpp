#include <memory>

#define MAX_REGISTERS 16

class StateElements {
    private:
        size_t program_counter;
        uint16_t current_instruction;
        uint16_t registers[MAX_REGISTERS];
    public:
        void set_instruction(uint16_t ins);
        uint16_t get_current_instruction();

        void set_program_counter(size_t pc);
        size_t get_program_counter();

        void set_register_value(uint16_t reg_index, uint16_t value);
        uint16_t get_register_value(uint16_t reg_index);
};
