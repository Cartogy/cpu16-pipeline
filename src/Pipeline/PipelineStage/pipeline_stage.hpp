#ifndef PIPELINE_STAGE
#define PIPELINE_STAGE
#include <memory>

#include "InstructionMemory/instruction_memory.hpp"
#include "PipelineRegister/pipeline_register.hpp"

class PipelineStage {
};

// Reponsible for starting the pipeline. Sets the valid bit on.
class PFetchStage : public PipelineStage {
    public:
        IfDecReg<uint16_t> exec(InstructionMemory<uint16_t> ins_mem, uint16_t program_counter);
};

class PDecodeStage : public PipelineStage {
    public:
        DecExecReg<uint16_t, uint16_t> exec(uint16_t *register_file, IfDecReg<uint16_t> reg);
};

class PExecStage : public PipelineStage {
    public:
        ExecMemReg<uint16_t, uint16_t> exec(DecExecReg<uint16_t, uint16_t> reg);
};

#endif
