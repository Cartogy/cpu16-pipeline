#include <cstdint>
#include <gtest/gtest.h>

#include "InstructionMemory/instruction_memory.hpp"
#include "PipelineRegister/pipeline_register.hpp"
#include "ControlUnit/control_unit_16.hpp"
#include "PipelineStage/pipeline_stage.hpp"
#include "StateElements/state_elements.hpp"
#include "Memory/memory.hpp"

class PipelineStageTest : public ::testing::Test {
    protected:
        InstructionMemory<uint16_t> ins_mem;
        Memory mem;
        StateElements se;
        ControlUnit16 cu;
        ALU16 alu;


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

        mem.store(0, 10);
        mem.store(2, 24);
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

    //TODO: Implement OP Tests...
    ControlOp cop = cu.control_op(add_ins);

    // setup fetch register pipeline
    IfDecReg<uint16_t> fetch_reg;
    fetch_reg.set_valid(true);
    fetch_reg.instruction = add_ins;   // add instruction

    // Test the pipeline register
    DecExecReg<uint16_t, uint16_t> reg = decode_stage.exec(se.get_register_file(), fetch_reg, cu);

    // Test Op Values
    EXPECT_TRUE(cop.exec_op == reg.exec_op);
    EXPECT_TRUE(cop.mem_op == reg.mem_op);
    EXPECT_TRUE(cop.write_op == reg.write_op);



    EXPECT_EQ(se.get_register_value(0), reg.read_one);
    EXPECT_EQ(se.get_register_value(1), reg.read_two);
}

TEST_F(PipelineStageTest, DecodeStageICategoryMemoryLoad) {
    PDecodeStage decode_stage;

    // setup fetch register pipeline
    IfDecReg<uint16_t> fetch_reg;
    fetch_reg.set_valid(true);
    fetch_reg.instruction = load_ins;   // load instruction
    ControlOp cop = cu.control_op(load_ins);

    // Test the pipeline register
    DecExecReg<uint16_t, uint16_t> reg = decode_stage.exec(se.get_register_file(), fetch_reg, cu);

    EXPECT_TRUE(cop.exec_op == reg.exec_op);
    EXPECT_TRUE(cop.mem_op == reg.mem_op);
    EXPECT_TRUE(cop.write_op == reg.write_op);

    // store the base address from the register.
    EXPECT_EQ(se.get_register_value(0), reg.read_one);
    // store the offset
    EXPECT_EQ(3, reg.imm_value);
}

TEST_F(PipelineStageTest, DecodeStageICategoryMemoryStore) {
    PDecodeStage decode_stage;

    // setup fetch register pipeline
    IfDecReg<uint16_t> fetch_reg;
    fetch_reg.set_valid(true);
    fetch_reg.instruction = store_ins;   // load instruction
    ControlOp cop = cu.control_op(store_ins);

    // Test the pipeline register
    DecExecReg<uint16_t, uint16_t> reg = decode_stage.exec(se.get_register_file(), fetch_reg, cu);

    EXPECT_TRUE(cop.exec_op == reg.exec_op);
    EXPECT_TRUE(cop.mem_op == reg.mem_op);
    EXPECT_TRUE(cop.write_op == reg.write_op);

    // store the base address from the register.
    EXPECT_EQ(se.get_register_value(0), reg.read_one);
    // store the offset
    EXPECT_EQ(5, reg.imm_value);

}

TEST_F(PipelineStageTest, DecodeStageICategoryImm) {
    PDecodeStage decode_stage;
    
    // setup fetch register pipeline
    IfDecReg<uint16_t> fetch_reg;
    fetch_reg.set_valid(true);
    fetch_reg.instruction = addi_ins;   // addi instruction
    ControlOp cop = cu.control_op(addi_ins);

    // Test
    DecExecReg<uint16_t, uint16_t> reg = decode_stage.exec(se.get_register_file(), fetch_reg, cu);

    EXPECT_TRUE(cop.exec_op == reg.exec_op);
    EXPECT_TRUE(cop.mem_op == reg.mem_op);
    EXPECT_TRUE(cop.write_op == reg.write_op);

    EXPECT_EQ(se.get_register_value(0), reg.read_one);
    EXPECT_EQ(4, reg.imm_value);
}

TEST_F(PipelineStageTest, DecodeStageICategoryBranch) {
    PDecodeStage decode_stage;
    
    // setup fetch register pipeline
    IfDecReg<uint16_t> fetch_reg;
    fetch_reg.set_valid(true);
    fetch_reg.instruction = bne_ins;   // addi instruction
    ControlOp cop = cu.control_op(bne_ins);

    DecExecReg<uint16_t, uint16_t> reg = decode_stage.exec(se.get_register_file(), fetch_reg, cu);

    // Test results
    EXPECT_TRUE(cop.exec_op == reg.exec_op);
    EXPECT_TRUE(cop.mem_op == reg.mem_op);
    EXPECT_TRUE(cop.write_op == reg.write_op);

    EXPECT_EQ(4, reg.read_one);
    EXPECT_EQ(8, reg.imm_value);
}

TEST_F(PipelineStageTest, DecodeStageJCategory) {
    PDecodeStage decode_stage;
    
    // setup fetch register pipeline
    IfDecReg<uint16_t> fetch_reg;
    fetch_reg.set_valid(true);
    fetch_reg.instruction = jmp_ins;   // addi instruction
    ControlOp cop = cu.control_op(jmp_ins);
    DecExecReg<uint16_t, uint16_t> reg = decode_stage.exec(se.get_register_file(), fetch_reg, cu);

    // Test results
    EXPECT_TRUE(cop.exec_op == reg.exec_op);
    EXPECT_TRUE(cop.mem_op == reg.mem_op);
    EXPECT_TRUE(cop.write_op == reg.write_op);

    EXPECT_EQ(0x010a, reg.jmp_address);

}

/** Execute Stage **/
TEST_F(PipelineStageTest, ExecStageRCategory) {
    PExecStage exec_stage;

    // Prepare DecExec register
    DecExecReg<uint16_t, uint16_t> dec_reg;
    ControlOp cop = cu.control_op(add_ins);
    dec_reg.exec_op = cop.exec_op;
    dec_reg.mem_op = cop.mem_op;
    dec_reg.write_op = cop.write_op;

    dec_reg.op_code = ((0xf << 12) & add_ins ) >> 12;

    dec_reg.read_one = 4;
    dec_reg.read_two = 2;

    ExecMemReg<uint16_t, uint16_t> reg = exec_stage.exec(dec_reg, alu);
    
    EXPECT_TRUE(cop.mem_op == reg.mem_op);
    EXPECT_TRUE(cop.write_op == reg.write_op);

    EXPECT_EQ(6, reg.alu_value);

/*    dec_reg.control_op = sub_ins;   // sub instruction
    reg = exec_stage.exec(dec_reg, alu);

    EXPECT_EQ(sub_ins, reg.control_op);
    EXPECT_EQ(2, reg.alu_value);
    */
}

TEST_F(PipelineStageTest, ExecStageICategoryMemory) {
    PExecStage exec_stage;

    // Prepare DecExec register
    DecExecReg<uint16_t, uint16_t> dec_reg;
    dec_reg.set_valid(true);

    ControlOp cop = cu.control_op(load_ins);
    dec_reg.exec_op = cop.exec_op;
    dec_reg.mem_op = cop.mem_op;
    dec_reg.write_op = cop.write_op;

    dec_reg.op_code = ((0xf << 12) & load_ins) >> 12;

    dec_reg.read_one = 4;
    dec_reg.imm_value = 3;

    ExecMemReg<uint16_t, uint16_t> reg = exec_stage.exec(dec_reg, alu);

    EXPECT_TRUE(cop.mem_op == reg.mem_op);
    EXPECT_TRUE(cop.write_op == reg.write_op);

    EXPECT_EQ(7, reg.alu_value);

    /* store instruction */

/*    dec_reg.control_op = store_ins;

    reg = exec_stage.exec(dec_reg, alu);

    EXPECT_EQ(store_ins, reg.control_op);
    EXPECT_EQ(7, reg.alu_value);
    */
}

TEST_F(PipelineStageTest, ExecStageICategoryImm) {
    PExecStage exec_stage;

    // Prepare DecExec register
    DecExecReg<uint16_t, uint16_t> dec_reg;
    dec_reg.set_valid(true);

    ControlOp cop = cu.control_op(addi_ins);
    dec_reg.exec_op = cop.exec_op;
    dec_reg.mem_op = cop.mem_op;
    dec_reg.write_op = cop.write_op;

    dec_reg.op_code = ((0xf << 12) & addi_ins) >> 12;

    dec_reg.read_one = 4;
    dec_reg.imm_value = 4;

    ExecMemReg<uint16_t, uint16_t> reg = exec_stage.exec(dec_reg, alu);

    EXPECT_TRUE(cop.mem_op == reg.mem_op);
    EXPECT_TRUE(cop.write_op == reg.write_op);

    EXPECT_EQ(8, reg.alu_value);
}

TEST_F(PipelineStageTest, ExecStageICategoryBranch) {
    PExecStage exec_stage;

    // Prepare DecExec register
    DecExecReg<uint16_t, uint16_t> dec_reg;
    dec_reg.set_valid(true);

    ControlOp cop = cu.control_op(bne_ins);
    dec_reg.exec_op = cop.exec_op;
    dec_reg.mem_op = cop.mem_op;
    dec_reg.write_op = cop.write_op;

    dec_reg.op_code = ((0xf << 12) & bne_ins) >> 12;

    dec_reg.read_one = 4;
    dec_reg.read_two = 2;
    dec_reg.imm_value = 8;

    ExecMemReg<uint16_t, uint16_t> reg = exec_stage.exec(dec_reg, alu);

    EXPECT_TRUE(cop.mem_op == reg.mem_op);
    EXPECT_TRUE(cop.write_op == reg.write_op);

    EXPECT_EQ(2, reg.alu_value);
}

TEST_F(PipelineStageTest, ExecStageJCategory) {
    PExecStage exec_stage;

    // Prepare DecExec register
    DecExecReg<uint16_t, uint16_t> dec_reg;
    dec_reg.set_valid(true);

    ControlOp cop = cu.control_op(jmp_ins);
    dec_reg.exec_op = cop.exec_op;
    dec_reg.mem_op = cop.mem_op;
    dec_reg.write_op = cop.write_op;

    dec_reg.op_code = ((0xf << 12) & jmp_ins) >> 12;

    dec_reg.jmp_address = 0x010a;

    ExecMemReg<uint16_t, uint16_t> reg = exec_stage.exec(dec_reg, alu);

    EXPECT_TRUE(cop.mem_op == reg.mem_op);
    EXPECT_TRUE(cop.write_op == reg.write_op);

    EXPECT_EQ(0x010a, reg.jmp_address);
}

/** Memory Stage **/
TEST_F(PipelineStageTest, MemoryStageRCategoryAdd) {
    PMemStage mem_stage;

    ExecMemReg<uint16_t, uint16_t> exec_reg;
    exec_reg.set_valid(true);
    /** Add instruction **/
    // Prepare control op
    ControlOp cop = cu.control_op(add_ins);
    exec_reg.mem_op = cop.mem_op;
    exec_reg.write_op = cop.write_op;

    exec_reg.alu_value = 6;
    exec_reg.write_back_address = 2;

    std::tuple<MemWriteReg<uint16_t, uint16_t>, uint16_t, uint16_t> reg_pcsrc_nextins = mem_stage.exec(mem, exec_reg);

    EXPECT_TRUE(cop.write_op == std::get<0>(reg_pcsrc_nextins).write_op);

    EXPECT_EQ(6, std::get<0>(reg_pcsrc_nextins).alu_value);

    uint16_t pc_src = 0;
    EXPECT_EQ(pc_src, std::get<1>(reg_pcsrc_nextins));

    EXPECT_EQ(2, std::get<0>(reg_pcsrc_nextins).write_back_address);
}

TEST_F(PipelineStageTest, MemoryStageRCategorySub) {
    PMemStage mem_stage;

    ExecMemReg<uint16_t, uint16_t> exec_reg;
    exec_reg.set_valid(true);

    // Prepare control op
    ControlOp cop = cu.control_op(sub_ins);
    exec_reg.mem_op = cop.mem_op;
    exec_reg.write_op = cop.write_op;

    // Prepare register values
    exec_reg.alu_value = 2;
    exec_reg.write_back_address = 2;

    // Execute stage
    std::tuple<MemWriteReg<uint16_t, uint16_t>, uint16_t, uint16_t> reg_pcsrc_nextins = mem_stage.exec(mem, exec_reg);

    /* Testing */
    EXPECT_TRUE(cop.write_op == std::get<0>(reg_pcsrc_nextins).write_op);

    EXPECT_EQ(2, std::get<0>(reg_pcsrc_nextins).alu_value);

    uint16_t pc_src = 0;
    EXPECT_EQ(pc_src, std::get<1>(reg_pcsrc_nextins));

    EXPECT_EQ(2, std::get<0>(reg_pcsrc_nextins).write_back_address);
}

TEST_F(PipelineStageTest, WriteStageRCategoryAdd) {
    PWriteStage write_stage;

    MemWriteReg<uint16_t, uint16_t> mem_reg;
    mem_reg.set_valid(true);

    // Prepare control op
    mem_reg.write_op.reg_write = 1;
    mem_reg.write_op.mem_to_reg = 0;

    // Prepare register values
    mem_reg.alu_value = 6;
    mem_reg.write_back_address = 2;

    UpdateArch<uint16_t, uint16_t> write_value = write_stage.exec(mem_reg);

    EXPECT_EQ(true, write_value.write);
    EXPECT_EQ(6, write_value.value);
    EXPECT_EQ(2, write_value.reg_index);

}

