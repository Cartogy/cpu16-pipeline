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
};

template<typename T, typename U>
struct DecExecReg : PipelineRegister {
        T control_op;
        U value_one;
        U value_two;
};

template <typename T, typename U>
struct ExecMemReg : PipelineRegister {
        T control_op;
        U value;
};

template <typename T, typename U>
struct MemWriteReg: PipelineRegister {
        T control_op;
        U value;
        bool take_branch;

};

/** Value used to decide whether to write or not to the registers **/
template <typename T, typename U>
struct UpdateArch {
    bool write;
    U value;
    T reg_index;
};


#endif
