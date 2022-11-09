#include <cstdint>
#include <gtest/gtest.h>

#include "InstructionMemory/instruction_memory.hpp"
#include "PipelineRegister/pipeline_register.hpp"
#include "PipelineStage/pipeline_stage.hpp"
#include "StateElements/state_elements.hpp"

class PipelineStageTest : public ::testing::Test {
    protected:
        InstructionMemory<uint16_t> ins_mem;
        StateElements se;

    void SetUp() override {
        ins_mem.add_instruction(0);
        ins_mem.add_instruction(1);

        se.set_register_value(0, 4);
        se.set_register_value(1, 2);
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

TEST_F(PipelineStageTest, DecodeStageRCategory) {
    PDecodeStage decode_stage;

    // setup fetch register pipeline
    IfDecReg<uint16_t> fetch_reg;
    fetch_reg.set_valid(true);
    fetch_reg.instruction = 0x4012;   // add instruction

    // Test the pipeline register
    DecExecReg<uint16_t, uint16_t> reg = decode_stage.exec(se.get_register_file(), fetch_reg);

    EXPECT_EQ(0x4012, reg.control_op);
    EXPECT_EQ(se.get_register_value(0), reg.value_one);
    EXPECT_EQ(se.get_register_value(1), reg.value_two);

    fetch_reg.instruction = 0x5012;   // sub instruction

    reg = decode_stage.exec(se.get_register_file(), fetch_reg);

    EXPECT_EQ(0x5012, reg.control_op);
    EXPECT_EQ(se.get_register_value(0), reg.value_one);
    EXPECT_EQ(se.get_register_value(1), reg.value_two);
}

TEST_
