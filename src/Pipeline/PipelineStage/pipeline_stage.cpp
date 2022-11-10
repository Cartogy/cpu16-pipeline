
#include "PipelineStage/pipeline_stage.hpp"
#include "PipelineRegister/pipeline_register.hpp"
#include "Memory/memory.hpp"

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
    dec_reg.set_valid(true);
    dec_reg.control_op = reg.instruction;
    dec_reg.value_one = 0;
    dec_reg.value_two = 0;


    if (0x8000 & reg.instruction) {
        // Implement Memory instructions.
        uint16_t top_four_bits = (0xf000 & reg.instruction) >> 12;
        // 0xc -> 12
        // All instructions under 12 sstore the same pattern.
        if (top_four_bits < 0xc) {  // Load/Store and immediate
            // acquire base address
            uint16_t base_index = ((0xf << 8) & reg.instruction) >> 8;
            uint16_t offset = 0xf & reg.instruction;

            dec_reg.value_one = register_file[base_index];
            dec_reg.value_two = offset;

        } else {
            // Branches and stuff
            /* Branches for now */
            uint16_t reg_one_index = ((0xf << 8) & reg.instruction) >> 8;
            uint16_t reg_two_index = ((0xf << 4) & reg.instruction) >> 4;

            dec_reg.value_one = register_file[reg_one_index];
            dec_reg.value_two = register_file[reg_two_index];
        }

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
        uint16_t jump = 0x0fff & reg.instruction;
        dec_reg.value_one = jump;
        std::cout << "J Instruction" << std::endl;
    }

    return dec_reg;
}

ExecMemReg<uint16_t, uint16_t> PExecStage::exec(DecExecReg<uint16_t, uint16_t> reg) {
    uint16_t op_code = ((0xf << 12) & reg.control_op) >> 12;

    ExecMemReg<uint16_t, uint16_t> exec_reg;

    exec_reg.set_valid(true);
    exec_reg.control_op = reg.control_op;
    
    if (op_code & 0x8) {    // I type instruction
        if (op_code > 0x9) {
            if (op_code >= 0xc) {   // branching
                exec_reg.value = reg.value_one - reg.value_two;
            } else {        // immediate
                if (op_code == 0xa) {       // addi
                    exec_reg.value = reg.value_one + reg.value_two;
                } else {                    // subi (0xb)
                    exec_reg.value = reg.value_one - reg.value_two;
                }
            }
        } else {    // load/store instructions
            exec_reg.value = reg.value_one + reg.value_two;
        }
    }  else if (op_code & 0x4) {    // R-Type
        // Need to check bits 
        if (op_code == 0x4) {
            exec_reg.value = reg.value_one + reg.value_two;
        } else if (op_code == 0x5) {
            exec_reg.value = reg.value_one - reg.value_two;
        } else if (op_code == 0x6) {
            exec_reg.value = reg.value_one * reg.value_two;
        } else {
            exec_reg.value = reg.value_one / reg.value_two;
        }
    } else {    // J-Type
        exec_reg.value = reg.value_one + 0;
    }

    return exec_reg;
}

MemWriteReg<uint16_t, uint16_t> PMemStage::exec(Memory mem, ExecMemReg<uint16_t, uint16_t> reg) {
    MemWriteReg<uint16_t, uint16_t> mem_reg;
    mem_reg.set_valid(true);

    uint16_t op_code = ((0xf << 12) & mem_reg.control_op) >> 12;

    // Check type of instruction
    // Either use memory or not depending if it is load/store.
    if (op_code == 0x8) {   // load
        uint16_t val = mem.load(reg.value); 
    } else if (op_code == 0x9) {  // store

    } else {
        mem_reg.value = reg.value;
    }

    return mem_reg;
}
