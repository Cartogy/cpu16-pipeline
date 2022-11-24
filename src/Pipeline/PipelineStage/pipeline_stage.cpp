
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
    /* Fill Opcode */
    uint16_t op_code = ((0xf << 12) & reg.instruction) >> 12;

    /* Fill R-type instruction fields */
    uint16_t reg_one = ((0xf << 8) & reg.instruction) >> 8;
    uint16_t reg_two = ((0xf << 4) & reg.instruction) >> 4;
    uint16_t dst_one_r = 0xf & reg.instruction;

    /* Fill R-type instruction fields */
    uint16_t imm_value = 0xf & reg.instruction;
    uint16_t dst_two_i = (0xf << 4) & reg.instruction;

    /* Fill J-type instruction fields */
    uint16_t jmp_address = 0xfff & reg.instruction;

    /* Opcode */
    dec_reg.op_code = op_code;

    // R-Type
    dec_reg.read_one = register_file[reg_one];
    dec_reg.read_two = register_file[reg_two];
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

ExecMemReg<uint16_t, uint16_t> PExecStage::exec(DecExecReg<uint16_t, uint16_t> reg, const ALU16& alu) {

    uint16_t value_one = reg.read_one;
    uint16_t value_two = 0;

    // ALU 2nd Input.
    if (reg.exec_op.alu_src == 1) {
        value_two = reg.imm_value;
    } else {
        value_two = reg.read_two;
    }

    // RegtoDst
    uint16_t reg_dst = 0;
    if (reg.exec_op.reg_dst == 0) {
        reg_dst = reg.dst_one_r;
    } else {
        reg_dst = reg.dst_two_i;
    }

    uint16_t branched_address = reg.imm_value + reg.pc_increment;

    ExecMemReg<uint16_t, uint16_t> exec_reg;

    /* Passing Values */
    exec_reg.mem_op = reg.mem_op;
    exec_reg.write_op = reg.write_op;
    exec_reg.jmp_address = reg.jmp_address;
    exec_reg.read_two = reg.read_two;

    exec_reg.write_back_address = reg_dst;
    exec_reg.zero = value_one - value_two;
    exec_reg.pc_branch = branched_address;

    uint16_t alu_value = alu.compute(value_one, value_two, ALU16::alu_op(reg.op_code));
    exec_reg.alu_value = alu_value;

    exec_reg.set_valid(true);

    return exec_reg;
}

std::tuple<MemWriteReg<uint16_t, uint16_t>, uint16_t, uint16_t> PMemStage::exec(Memory mem, ExecMemReg<uint16_t, uint16_t> reg) {
    MemWriteReg<uint16_t, uint16_t> mem_reg;
    mem_reg.set_valid(true);


    uint16_t op_code = ((0xf << 12) & mem_reg.control_op) >> 12;
    // pass values
    mem_reg.write_op = reg.write_op;
    mem_reg.write_back_address = reg.write_back_address;
    mem_reg.alu_value = reg.alu_value;

    // Memory Access
    if (reg.mem_op.mem_read) {
        mem_reg.data_out = mem.load(mem_reg.alu_value);
    }
    if (reg.mem_op.mem_write) {
        mem.store(reg.alu_value, reg.read_two);
    }

    /* Branch/Jump Address */
    bool valid_branch = reg.mem_op.branch && (reg.zero == 0);

    // Determine PCSrc
    uint16_t pc_src = 0;
    if (valid_branch || reg.mem_op.jmp > 0) {
        pc_src = 1;
    }

    // Determine branch or jump
    uint16_t next_instruction = 0;
    if (reg.mem_op.jmp == 0) {
        next_instruction = reg.pc_branch;
    } else {
        next_instruction = reg.jmp_address;
    }

    /* Output PCSrc and branched address */

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
    return {mem_reg, pc_src, next_instruction};
}
