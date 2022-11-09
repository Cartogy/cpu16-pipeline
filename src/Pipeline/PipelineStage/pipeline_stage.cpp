
#include "PipelineStage/pipeline_stage.hpp"
#include "PipelineRegister/pipeline_register.hpp"

IfDecReg<uint16_t> PFetchStage::exec(InstructionMemory<uint16_t> ins_mem, uint16_t program_counter) {
    IfDecReg<uint16_t> reg;

    reg.instruction = ins_mem.get_instruction(program_counter);
    // The beginning of the pipeline.
    reg.set_valid(true);
    return reg;
}

DecExecReg<uint16_t, uint16_t> PDecodeStage::exec(uint16_t *register_file, IfDecReg<uint16_t> reg) {
    // Check instruction type
    // 1000|++++|++++|++++| -> I-Type
    // 0100|++++|++++|++++| -> R-Type
    // 0010|++++++++++++| -> J-Type
    
    DecExecReg<uint16_t, uint16_t> dec_reg;
    dec_reg.set_valid(1);
    dec_reg.control_op = reg.instruction;
    dec_reg.value_one = 0;
    dec_reg.value_two = 0;


    if (0x8000 & reg.instruction) {
        // Is I-Type
        std::cout << "I Instruction" << std::endl;
    } else if (0x4000 & reg.instruction) {
        std::cout << "R Instruction" << std::endl;
        // Acquire reg index from instruction.
        // Src 1
        uint16_t reg_one_index = ((0xf << 8) & reg.instruction) >> 8;
        // Src 2
        uint16_t reg_two_index = ((0xf << 4) & reg.instruction) >> 4;

        // Store in register.
        dec_reg.value_one = register_file[reg_one_index];
        dec_reg.value_two = register_file[reg_two_index];

    } else {
        std::cout << "J Instruction" << std::endl;
    }

    return dec_reg;
}
