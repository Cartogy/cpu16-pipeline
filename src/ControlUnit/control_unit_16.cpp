#include "control_unit_16.hpp"

/* Takes only the op-code */
ControlOp ControlUnit16::control_op(uint16_t op) {
    struct ExecOp exec_op;
    struct MemOp mem_op;
    struct WriteOp write_op;

    // default for write
    write_op.mem_to_reg = 0;
    write_op.reg_write = 0;

    if (op >= ((2*2*2)+(2*2)) ) {   // 1100
        exec_op.alu_src = 0;
        exec_op.reg_dst = 0;

        mem_op.mem_write = 0;
        mem_op.mem_read = 0;

        mem_op.branch = 1;
        mem_op.jmp = 0;
    } else if (op >= (2*2*2)) { // 1000
        exec_op.alu_src = 1;
        exec_op.reg_dst = 1;

        mem_op.mem_write = 0;
        mem_op.mem_read = 0;
        mem_op.branch = 0;
        mem_op.jmp = 0;

        write_op.reg_write = 1;
        write_op.mem_to_reg = 0;

        // Check if load/store
        if (op == 0x8) {    // LOAD
            mem_op.mem_read = 1;
            write_op.mem_to_reg = 1;
        } 
        if (op == 0x9) {    // STORE
            mem_op.mem_write = 1;
        }

    } else if (op >= (2*2)) {   //  0100
        exec_op.alu_src = 0;    
        exec_op.reg_dst = 0;

        mem_op.mem_write = 0;
        mem_op.mem_read = 0;
        mem_op.branch = 0;
        mem_op.jmp = 0;

        write_op.reg_write = 1;
    } else {                    // 0010
        exec_op.alu_src = 1;
        exec_op.reg_dst = 0;

        mem_op.mem_write = 0;
        mem_op.mem_read = 0;
        mem_op.branch = 0;
        mem_op.jmp = 1;

    }

    // The PCSrc is passed to the Fetch Stage after execution.
    //exec_op.pc_src = mem_op.jmp | mem_op.branch;

    struct ControlOp control_op;
    control_op.write_op = write_op;
    control_op.exec_op = exec_op;
    control_op.mem_op = mem_op;

    return control_op;
}
