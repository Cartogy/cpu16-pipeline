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

        uint16_t add_ins = 0x4012;
        uint16_t sub_ins = 0x5012;
        uint16_t load_ins = 0x8013;
        uint16_t store_ins = 0x9015;
        uint16_t addi_ins = 0xa014;
        uint16_t bne_ins = 0xc018;
        uint16_t jmp_ins = 0x210a;

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
    fetch_reg.instruction = add_ins;   // add instruction

    // Test the pipeline register
    DecExecReg<uint16_t, uint16_t> reg = decode_stage.exec(se.get_register_file(), fetch_reg);

    EXPECT_EQ(0x4012, reg.control_op);
    EXPECT_EQ(se.get_register_value(0), reg.value_one);
    EXPECT_EQ(se.get_register_value(1), reg.value_two);

    fetch_reg.instruction = sub_ins;   // sub instruction

    reg = decode_stage.exec(se.get_register_file(), fetch_reg);

    EXPECT_EQ(0x5012, reg.control_op);
    EXPECT_EQ(se.get_register_value(0), reg.value_one);
    EXPECT_EQ(se.get_register_value(1), reg.value_two);
}

TEST_F(PipelineStageTest, DecodeStageICategoryMemory) {
    PDecodeStage decode_stage;

    // setup fetch register pipeline
    IfDecReg<uint16_t> fetch_reg;
    fetch_reg.set_valid(true);
    fetch_reg.instruction = load_ins;   // load instruction

    // Test the pipeline register
    DecExecReg<uint16_t, uint16_t> reg = decode_stage.exec(se.get_register_file(), fetch_reg);

    EXPECT_EQ(0x8013, reg.control_op);
    // store the base address from the register.
    EXPECT_EQ(se.get_register_value(0), reg.value_one);
    // store the offset
    EXPECT_EQ(3, reg.value_two);

    fetch_reg.instruction = store_ins; // store instruction
    reg = decode_stage.exec(se.get_register_file(), fetch_reg);

    EXPECT_EQ(0x9015, reg.control_op);
    // get the base address from the register.
    EXPECT_EQ(se.get_register_value(0), reg.value_one);
    // get the offset
    EXPECT_EQ(5, reg.value_two);
}

TEST_F(PipelineStageTest, DecodeStageICategoryImm) {
    PDecodeStage decode_stage;
    
    // setup fetch register pipeline
    IfDecReg<uint16_t> fetch_reg;
    fetch_reg.set_valid(true);
    fetch_reg.instruction = addi_ins;   // addi instruction

    // Test
    DecExecReg<uint16_t, uint16_t> reg = decode_stage.exec(se.get_register_file(), fetch_reg);

    EXPECT_EQ(0xa014, reg.control_op);
    EXPECT_EQ(se.get_register_value(0), reg.value_one);
    EXPECT_EQ(4, reg.value_two);
}

TEST_F(PipelineStageTest, DecodeStageICategoryBranch) {
    PDecodeStage decode_stage;
    
    // setup fetch register pipeline
    IfDecReg<uint16_t> fetch_reg;
    fetch_reg.set_valid(true);
    fetch_reg.instruction = bne_ins;   // addi instruction

    DecExecReg<uint16_t, uint16_t> reg = decode_stage.exec(se.get_register_file(), fetch_reg);

    // Test results
    EXPECT_EQ(bne_ins, reg.control_op);
    EXPECT_EQ(4, reg.value_one);
    EXPECT_EQ(2, reg.value_two);
}

TEST_F(PipelineStageTest, DecodeStageJCategory) {
    PDecodeStage decode_stage;
    
    // setup fetch register pipeline
    IfDecReg<uint16_t> fetch_reg;
    fetch_reg.set_valid(true);
    fetch_reg.instruction = jmp_ins;   // addi instruction

    DecExecReg<uint16_t, uint16_t> reg = decode_stage.exec(se.get_register_file(), fetch_reg);

    // Test results
    EXPECT_EQ(jmp_ins, reg.control_op);
    EXPECT_EQ(0x010a, reg.value_one);

}

/** Execute Stage **/
TEST_F(PipelineStageTest, ExecStageRCategory) {
    PExecStage exec_stage;

    // Prepare DecExec register
    DecExecReg<uint16_t, uint16_t> dec_reg;
    dec_reg.control_op = add_ins;           // add instruction
    dec_reg.value_one = 4;
    dec_reg.value_two = 2;

    ExecMemReg<uint16_t, uint16_t> reg = exec_stage.exec(dec_reg);
    
    EXPECT_EQ(add_ins, reg.control_op);
    EXPECT_EQ(6, reg.value);

    dec_reg.control_op = sub_ins;   // sub instruction
    reg = exec_stage.exec(dec_reg);

    EXPECT_EQ(sub_ins, reg.control_op);
    EXPECT_EQ(2, reg.value);
}

TEST_F(PipelineStageTest, ExecStageICategoryMemory) {
    PExecStage exec_stage;

    // Prepare DecExec register
    DecExecReg<uint16_t, uint16_t> dec_reg;
    dec_reg.set_valid(true);

    dec_reg.control_op = load_ins;           // load instruction
    dec_reg.value_one = 4;
    dec_reg.value_two = 3;

    ExecMemReg<uint16_t, uint16_t> reg = exec_stage.exec(dec_reg);

    EXPECT_EQ(load_ins, reg.control_op);
    EXPECT_EQ(7, reg.value);

    /* store instruction */

    dec_reg.control_op = store_ins;

    reg = exec_stage.exec(dec_reg);

    EXPECT_EQ(store_ins, reg.control_op);
    EXPECT_EQ(7, reg.value);
}

TEST_F(PipelineStageTest, ExecStageICategoryImm) {
    PExecStage exec_stage;

    // Prepare DecExec register
    DecExecReg<uint16_t, uint16_t> dec_reg;
    dec_reg.set_valid(true);

    dec_reg.control_op = addi_ins;           // addi instruction
    dec_reg.value_one = 4;
    dec_reg.value_two = 4;

    ExecMemReg<uint16_t, uint16_t> reg = exec_stage.exec(dec_reg);
    EXPECT_EQ(addi_ins, reg.control_op);
    EXPECT_EQ(8, reg.value);
}

TEST_F(PipelineStageTest, ExecStageICategoryBranch) {
    PExecStage exec_stage;

    // Prepare DecExec register
    DecExecReg<uint16_t, uint16_t> dec_reg;
    dec_reg.set_valid(true);

    dec_reg.control_op = bne_ins;           // bne instruction
    dec_reg.value_one = 4;
    dec_reg.value_two = 2;

    ExecMemReg<uint16_t, uint16_t> reg = exec_stage.exec(dec_reg);
    EXPECT_EQ(bne_ins, reg.control_op);
    EXPECT_EQ(2, reg.value);
}

TEST_F(PipelineStageTest, ExecStageJCategory) {
    PExecStage exec_stage;

    // Prepare DecExec register
    DecExecReg<uint16_t, uint16_t> dec_reg;
    dec_reg.set_valid(true);

    dec_reg.control_op = jmp_ins;           // bne instruction
    dec_reg.value_one = 0x010a;
    dec_reg.value_two = 0;

    ExecMemReg<uint16_t, uint16_t> reg = exec_stage.exec(dec_reg);
    EXPECT_EQ(jmp_ins, reg.control_op);
    EXPECT_EQ(0x010a, reg.value);
}

/** Memory Stage **/
TEST_F(PipelineStageTest, MemoryStageRCategory) {
    PMemStage mem_stage;

    ExecMemReg<uint16_t, uint16_t> exec_reg;
    exec_reg.set_valid(true);
    /** Add instruction **/
    exec_reg.control_op = add_ins;
    exec_reg.value = 6;

    MemWriteReg<uint16_t, uint16_t> reg = mem_stage.exec(exec_reg);

    EXPECT_EQ(add_ins, reg.control_op);
    EXPECT_EQ(6, reg.value);

    /** Sub instruction **/
    exec_reg.control_op = sub_ins;
    exec_reg.value = 2;

    reg = mem_stage.exec(exec_reg);

    EXPECT_EQ(sub_ins, reg.control_op);
    EXPECT_EQ(2, reg.value);
}
