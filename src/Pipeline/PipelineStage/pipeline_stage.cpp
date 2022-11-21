
#include "PipelineStage/pipeline_stage.hpp"
#include "PipelineRegister/pipeline_register.hpp"
#include "Memory/memory.hpp"

IfDecReg<uint16_t> PFetchStage::exec(InstructionMemory<uint16_t> ins_mem, uint16_t program_counter) {
    IfDecReg<uint16_t> reg;

    reg.instruction = ins_mem.get_instruction(program_counter);
    reg.pc_increment = program_counter + 1; // point to the next instruction.
                                            
    // The beginning of the pipeline.
    reg.set_valid(true);
    return reg;
}

// DONE: Refactor pipeline stages
DecExecReg<uint16_t, uint16_t> PDecodeStage::exec(uint16_t *register_file, IfDecReg<uint16_t> reg, const ControlUnit16& control) {
    // Check instruction type
    // 1000|++++|++++|++++| -> I-Type
    // 0100|++++|++++|++++| -> R-Type
    // 0010|++++++++++++| -> J-Type

    DecExecReg<uint16_t, uint16_t> dec_reg;
    dec_reg.set_valid(true);
    /* Passing fields */
    dec_reg.pc_increment = reg.pc_increment;

    
    /* Default values */
    dec_reg.read_one = 0;
    dec_reg.read_two = 0;
    dec_reg.imm_value = 0;
    dec_reg.jmp_address = 0;
    dec_reg.dst_one_r = 0;
    dec_reg.dst_two_i = 0;

    /* Fill R-type instruction fields */
    uint16_t reg_one = ((0xf << 8) & reg.instruction) >> 12;
    uint16_t reg_two = ((0xf << 4) & reg.instruction) >> 8;
    uint16_t dst_one_r = 0xf & reg.instruction;

    /* Fill R-type instruction fields */
    uint16_t imm_value = 0xf & reg.instruction;
    uint16_t dst_two_i = (0xf << 4) & reg.instruction;

    /* Fill J-type instruction fields */
    uint16_t jmp_address = 0xfff & reg.instruction;

    // R-Type
    dec_reg.read_one = reg_one;
    dec_reg.read_two = reg_two;
    dec_reg.dst_one_r = dst_one_r;

    // I-Type
    dec_reg.imm_value = imm_value;
    dec_reg.dst_two_i = dst_two_i;

    // J-Type
    dec_reg.jmp_address = jmp_address;

    // Fill in the control op
    ControlOp control_op = control.control_op(reg.instruction);
    dec_reg.exec_op = control_op.exec_op;
    dec_reg.mem_op = control_op.mem_op;
    dec_reg.write_op = control_op.write_op;

    return dec_reg;
}

ExecMemReg<uint16_t, uint16_t> PExecStage::exec(DecExecReg<uint16_t, uint16_t> reg) {

    uint16_t op_code = ((0xf << 12) & reg.control_op) >> 12;

    ExecMemReg<uint16_t, uint16_t> exec_reg;

    exec_reg.set_valid(true);

    /* Passing Values */
    exec_reg.control_op = reg.control_op;
    /*
    exec_reg.write_back_address = reg.write_back_address;
    
    if (op_code & 0x8) {    // I type instruction
        if (op_code > 0x9) {
            if (op_code >= 0xc) {   // branching
                // Do comparison
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
            exec_reg.alu_value = reg.reg_one + reg.reg_two;
        } else if (op_code == 0x5) {
            exec_reg.alu_value = reg.reg_one - reg.reg_two;
        } else if (op_code == 0x6) {
            exec_reg.alu_value = reg.reg_one * reg.reg_two;
        } else {
            exec_reg.alu_value = reg.reg_one / reg.reg_two;
        }
    } else {    // J-Type
        exec_reg.branch_pc = reg.imm_value + 0;
    }
    */

    return exec_reg;
}

MemWriteReg<uint16_t, uint16_t> PMemStage::exec(Memory mem, ExecMemReg<uint16_t, uint16_t> reg) {
    MemWriteReg<uint16_t, uint16_t> mem_reg;
    mem_reg.set_valid(true);

    uint16_t op_code = ((0xf << 12) & mem_reg.control_op) >> 12;

    // Check type of instruction
    // Either use memory or not depending if it is load/store.
    /*
    if (op_code == 0x8) {   // load
        uint16_t val = mem.load(reg.value); 
    } else if (op_code == 0x9) {  // store

    } else {
        mem_reg.value = reg.value;
    }
    */
    return mem_reg;
}
