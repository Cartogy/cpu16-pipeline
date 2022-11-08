#include <gtest/gtest.h>

#include "InstructionMemory/instruction_memory.hpp"
#include "PipelineRegister/pipeline_register.hpp"
#include "PipelineStage/pipeline_stage.hpp"

class PipelineStageTest : public ::testing::Test {
    protected:
        InstructionMemory<uint16_t> ins_mem;

    void SetUp() override {
        ins_mem.add_instruction(0);
        ins_mem.add_instruction(1);
    }

};

TEST_F(PipelineStageTest, FetchStage) {
    PFetchStage fetch_stage;
    uint16_t program_counter = 0;

    // Check register has correct values.
    IfDecReg<uint16_t> ifdec_reg = fetch_stage.exec(ins_mem, program_counter);
    EXPECT_EQ(0, ifdec_reg.instruction);
    EXPECT_TRUE(ifdec_reg.is_valid());

    // point to next instruction
    program_counter++;

    ifdec_reg = fetch_stage.exec(ins_mem, program_counter);
    EXPECT_EQ(1, ifdec_reg.instruction);
    EXPECT_TRUE(ifdec_reg.is_valid());
}
