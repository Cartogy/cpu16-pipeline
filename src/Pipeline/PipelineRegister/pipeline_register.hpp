#ifndef PIPELINE_REGISTER
#define PIPELINE_REGISTER
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
        T control_op;
        T pc_increment;
        T write_back_address;
        U reg_one;
        U reg_two;
        U imm_value;
        U jmp_address;
};

template <typename T, typename U>
struct ExecMemReg : PipelineRegister {
        T control_op;
        T branch_pc;    // either branched or PC+4
        T write_back_address;
        U alu_value;
        U write_reg_data;
};

template <typename T, typename U>
struct MemWriteReg: PipelineRegister {
        T control_op;
        T write_back_address;
        U data_read;
        U alu_value;
};

/** Value used to decide whether to write or not to the registers **/
template <typename T, typename U>
struct UpdateArch {
    bool write;
    U value;
    T reg_index;
};


#endif
