
#include "PipelineStage/pipeline_stage.hpp"
#include "PipelineRegister/pipeline_register.hpp"

IfDecReg<uint16_t> PFetchStage::exec(InstructionMemory<uint16_t> ins_mem, uint16_t program_counter) {
    IfDecReg<uint16_t> reg;

    reg.instruction = ins_mem.get_instruction(program_counter);
    // The beginning of the pipeline.
    reg.set_valid(true);
    return reg;
}
