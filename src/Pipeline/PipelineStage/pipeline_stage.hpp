#ifndef PIPELINE_STAGE
#define PIPELINE_STAGE
#include <memory>

#include "ControlUnit/control_unit_16.hpp"
#include "InstructionMemory/instruction_memory.hpp"
#include "PipelineRegister/pipeline_register.hpp"
#include "Memory/memory.hpp"
#include "ALU/alu_16.hpp"

class PipelineStage {
};

// Reponsible for starting the pipeline. Sets the valid bit on.
class PFetchStage : public PipelineStage {
    public:
        IfDecReg<uint16_t> exec(InstructionMemory<uint16_t> ins_mem, uint16_t program_counter);
};

class PDecodeStage : public PipelineStage {
    public:
        DecExecReg<uint16_t, uint16_t> exec(uint16_t *register_file, IfDecReg<uint16_t> reg, const ControlUnit16& control_unit);
};

class PExecStage : public PipelineStage {
    public:
        ExecMemReg<uint16_t, uint16_t> exec(DecExecReg<uint16_t, uint16_t> reg, const ALU16& alu);
};

class PMemStage : public PipelineStage {
    public:
        std::tuple<MemWriteReg<uint16_t, uint16_t>, uint16_t, uint16_t> exec(Memory mem, ExecMemReg<uint16_t, uint16_t> reg);
};

class PWriteStage : public PipelineStage {
    public:
        UpdateArch<uint16_t, uint16_t> exec(MemWriteReg<uint16_t, uint16_t> reg);
};

#endif
