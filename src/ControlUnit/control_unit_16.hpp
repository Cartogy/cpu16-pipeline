#include <cstdint>
#include <memory>
#include "control_unit.hpp"

struct ExecOp {
    uint16_t alu_src;
    uint16_t reg_dst;
    uint16_t pc_src;

    public:
        bool operator==(const ExecOp& other) {
            return reg_dst == other.reg_dst && alu_src ==  other.alu_src;
        }

};

struct MemOp {
    uint16_t jmp;
    uint16_t mem_write;
    uint16_t mem_read;
    uint16_t branch;

    public:
        bool operator==(const MemOp& other) {
            return jmp == other.jmp && mem_write == other.mem_write && mem_read == other.mem_read && branch == other.branch;
        }
        
};

struct WriteOp {
    uint16_t mem_to_reg;
    public:
        bool operator==(const WriteOp& other) {
            return mem_to_reg == other.mem_to_reg;
        }
};

struct ControlOp {
    struct ExecOp exec_op;
    struct MemOp mem_op;
    struct WriteOp write_op;

    public:
        bool operator==(const ControlOp& other) {
            return exec_op == other.exec_op && write_op ==  other.write_op && mem_op == other.mem_op;
        }
        

};

class ControlUnit16 : public ControlUnit<uint16_t, ControlOp> {
    public:
        ControlOp control_op(uint16_t ins);

};


