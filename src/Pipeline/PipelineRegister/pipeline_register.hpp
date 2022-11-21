#ifndef PIPELINE_REGISTER
#define PIPELINE_REGISTER

#include "ControlUnit/control_unit_16.hpp"

/* pipeline Registers for a Pipeline Architecture */

struct PipelineRegister {
    protected:
        bool valid;
    public:
        bool is_valid();
        void set_valid(bool val);
};

/** Custom Pipeline Registers for each Pipeline Stage **/
template <typename T>
struct IfDecReg : PipelineRegister {
        T instruction;
        T pc_increment;
};

template<typename T, typename U>
struct DecExecReg : PipelineRegister {
        ExecOp exec_op;
        MemOp mem_op;
        WriteOp write_op;

        T pc_increment;
        T imm_value;
        T jmp_address;
        U read_one;
        U read_two;
        U dst_one_r;
        U dst_two_i;
};

template <typename T, typename U>
struct ExecMemReg : PipelineRegister {
        MemOp mem_op;
        WriteOp write_op;

        T jmp_address;
        T pc_branch;    // either branched or PC+4
        T write_back_address;
        U zero;
        U alu_value;
        U read_two;
};

template <typename T, typename U>
struct MemWriteReg: PipelineRegister {
        WriteOp write_op;

        T control_op;
        T write_back_address;
        U alu_value;
        U data_out;
};

/** Value used to decide whether to write or not to the registers **/
template <typename T, typename U>
struct UpdateArch {
    bool write;
    U value;
    T reg_index;
};
#endif
