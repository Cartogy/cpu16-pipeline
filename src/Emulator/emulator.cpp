#include "emulator.hpp"
#include "Pipeline/PipelineRegister/pipeline_register.hpp"

Emulator::Emulator() {}

void Emulator::add_instructions(std::vector<uint16_t> instructions) {

    for(uint16_t in : instructions) {
        instruction_memory.add_instruction(in);
    }

}
int Emulator::total_instructions() {
    return instruction_memory.total_instructions();
}

bool Emulator::valid_ifdec_reg() {
    return if_dec_register.is_valid();
}
bool Emulator::valid_decexec_reg() {
    return dec_exec_register.is_valid();
}
bool Emulator::valid_execmem_reg() {
    return exec_mem_register.is_valid();
}
bool Emulator::valid_memwrite_reg() {
    return mem_write_register.is_valid();
}

const IfDecReg<uint16_t>& Emulator::get_ifdec_reg() {
    return if_dec_register;
}
const DecExecReg<uint16_t, uint16_t>& Emulator::get_decexec_reg() {
    return dec_exec_register;
}
const ExecMemReg<uint16_t, uint16_t>& Emulator::get_execmem_reg() {
    return exec_mem_register;
}
const MemWriteReg<uint16_t, uint16_t>& Emulator::get_memwrite_reg() {
    return mem_write_register;
}

void Emulator::execute_clock_cycle() {
    // Write Back execution
    UpdateArch<uint16_t, uint16_t> to_write_data;

    to_write_data = writeback_stage.exec(mem_write_register);

    // Memory Stage Exection 
    std::tuple<MemWriteReg<uint16_t, uint16_t>, uint16_t, uint16_t> mem_stage_data = memory_stage.exec(memory, exec_mem_register);

    mem_write_register = std::get<0>(mem_stage_data);
    uint16_t pc_source = std::get<1>(mem_stage_data);
    uint16_t branched_instruction = std::get<2>(mem_stage_data);

    /** Set next instruction **/
    if (pc_source == 1) {
        state_elements.set_program_counter(branched_instruction);
    }

    // Execute Stage
    exec_mem_register = execute_stage.exec(dec_exec_register, alu);
    
    // Decode Stage
    dec_exec_register = decode_stage.exec(state_elements.get_register_file(), if_dec_register, control_unit);
    
    // Fetch Stage
    state_elements.set_program_counter(state_elements.get_program_counter()+1); // point to next instruction.

    if_dec_register = fetch_stage.exec(instruction_memory, state_elements.get_program_counter()); 
}

