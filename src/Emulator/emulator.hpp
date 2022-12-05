#include "InstructionMemory/instruction_memory.hpp"
#include "Memory/memory.hpp"
#include "StateElements/state_elements.hpp"
#include "Pipeline/PipelineStage/pipeline_stage.hpp"
#include "Pipeline/PipelineRegister/pipeline_register.hpp"
#include "ALU/alu_16.hpp"
#include "ControlUnit/control_unit_16.hpp"

class Emulator {
    private:
        InstructionMemory<uint16_t> instruction_memory;
        Memory memory;
        StateElements state_elements;
        ControlUnit16 control_unit;
        ALU16 alu;

        // Pipeline stages
        PFetchStage fetch_stage;
        PDecodeStage decode_stage;
        PExecStage execute_stage;
        PMemStage memory_stage;
        PWriteStage writeback_stage;

        /* Pipeline Registers */ 
        IfDecReg<uint16_t> if_dec_register;
        DecExecReg<uint16_t, uint16_t> dec_exec_register;
        ExecMemReg<uint16_t, uint16_t> exec_mem_register;
        MemWriteReg<uint16_t, uint16_t> mem_write_register;


    public:
        Emulator();
        
        void execute_clock_cycle();
        void run_instructions();

        void add_instructions(std::vector<uint16_t> instructions);
        int total_instructions();

        bool valid_ifdec_reg();
        bool valid_decexec_reg();
        bool valid_execmem_reg();
        bool valid_memwrite_reg();

        const IfDecReg<uint16_t>& get_ifdec_reg();
        const DecExecReg<uint16_t, uint16_t>& get_decexec_reg();
        const ExecMemReg<uint16_t, uint16_t>& get_execmem_reg();
        const MemWriteReg<uint16_t, uint16_t>& get_memwrite_reg();
};
