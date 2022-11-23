#include <gtest/gtest.h>
#include "ControlUnit/control_unit_16.hpp"

class ControlUnit16Test : public ::testing::Test {
    protected:
        ControlUnit16 control_unit;
        ControlOp zero;

    void SetUp() override {
        zero.exec_op.alu_src = 0;
        zero.exec_op.reg_dst = 0;

        zero.mem_op.branch = 0;
        zero.mem_op.jmp = 0;
        zero.mem_op.mem_read = 0;
        zero.mem_op.mem_write = 0;
        zero.write_op.mem_to_reg = 0;

    }

};

TEST_F(ControlUnit16Test, ControlOpJCategory) {

    uint16_t jmp_op = 0x2;
    ControlOp cop = control_unit.control_op(jmp_op);
    
    // Exec Jump
    ExecOp exec_op;
    exec_op.alu_src = 1;
    exec_op.reg_dst = 0;

    MemOp mem_op;
    mem_op.jmp = 1;
    mem_op.mem_write = 0;
    mem_op.mem_read = 0;
    mem_op.branch = 0;

    WriteOp write_op;
    write_op.mem_to_reg = 0;
    write_op.reg_write = 0;

    ControlOp control_op;
    control_op.exec_op = exec_op;
    control_op.mem_op = mem_op;
    control_op.write_op = write_op;
    
    //EXPECT_EQ(zero,cop);
    EXPECT_TRUE(control_op == cop);
}

TEST_F(ControlUnit16Test, ControlOpRCategoryAdd) {

    uint16_t add_op = 0x4;

    ControlOp cop = control_unit.control_op(add_op);
    
    // Exec Jump
    ExecOp exec_op;
    exec_op.alu_src = 0;
    exec_op.reg_dst = 0;

    MemOp mem_op;
    mem_op.jmp = 0;
    mem_op.mem_write = 0;
    mem_op.mem_read = 0;
    mem_op.branch = 0;

    WriteOp write_op;
    write_op.mem_to_reg = 0;
    write_op.reg_write = 1;

    ControlOp control_op;
    control_op.exec_op = exec_op;
    control_op.mem_op = mem_op;
    control_op.write_op = write_op;
    
    //EXPECT_EQ(zero,cop);
    EXPECT_TRUE(control_op == cop);
}

TEST_F(ControlUnit16Test, ControlOpICategoryLoad) {

    uint16_t load_op = 0x8;

    ControlOp cop = control_unit.control_op(load_op);
    
    // Exec Jump
    ExecOp exec_op;
    exec_op.alu_src = 1;
    exec_op.reg_dst = 1;

    MemOp mem_op;
    mem_op.jmp = 0;
    mem_op.mem_write = 0;
    mem_op.mem_read = 1;
    mem_op.branch = 0;

    WriteOp write_op;
    write_op.mem_to_reg = 1;
    write_op.reg_write = 1;

    ControlOp control_op;
    control_op.exec_op = exec_op;
    control_op.mem_op = mem_op;
    control_op.write_op = write_op;
    
    //EXPECT_EQ(zero,cop);
    EXPECT_TRUE(control_op == cop);
}

TEST_F(ControlUnit16Test, ControlOpICategoryStore) {

    uint16_t store_op = 0x9;

    ControlOp cop = control_unit.control_op(store_op);
    
    // Exec Jump
    ExecOp exec_op;
    exec_op.alu_src = 1;
    exec_op.reg_dst = 1;

    MemOp mem_op;
    mem_op.jmp = 0;
    mem_op.mem_write = 1;
    mem_op.mem_read = 0;
    mem_op.branch = 0;

    WriteOp write_op;
    write_op.mem_to_reg = 0;
    write_op.reg_write = 1;

    ControlOp control_op;
    control_op.exec_op = exec_op;
    control_op.mem_op = mem_op;
    control_op.write_op = write_op;
    
    //EXPECT_EQ(zero,cop);
    EXPECT_TRUE(control_op == cop);
}

TEST_F(ControlUnit16Test, ControlOpICategoryAddImm) {

    uint16_t addi_op = 0xa;

    ControlOp cop = control_unit.control_op(addi_op);
    
    // Exec Jump
    ExecOp exec_op;
    exec_op.alu_src = 1;
    exec_op.reg_dst = 1;

    MemOp mem_op;
    mem_op.jmp = 0;
    mem_op.mem_write = 0;
    mem_op.mem_read = 0;
    mem_op.branch = 0;

    WriteOp write_op;
    write_op.mem_to_reg = 0;
    write_op.reg_write = 1;

    ControlOp control_op;
    control_op.exec_op = exec_op;
    control_op.mem_op = mem_op;
    control_op.write_op = write_op;
    
    //EXPECT_EQ(zero,cop);
    EXPECT_TRUE(control_op == cop);
}

TEST_F(ControlUnit16Test, ControlOpICategorySubImm) {

    uint16_t subi_op = 0xb;

    ControlOp cop = control_unit.control_op(subi_op);
    
    // Exec Jump
    ExecOp exec_op;
    exec_op.alu_src = 1;
    exec_op.reg_dst = 1;

    MemOp mem_op;
    mem_op.jmp = 0;
    mem_op.mem_write = 0;
    mem_op.mem_read = 0;
    mem_op.branch = 0;

    WriteOp write_op;
    write_op.mem_to_reg = 0;
    write_op.reg_write = 1;

    ControlOp control_op;
    control_op.exec_op = exec_op;
    control_op.mem_op = mem_op;
    control_op.write_op = write_op;
    
    //EXPECT_EQ(zero,cop);
    EXPECT_TRUE(control_op == cop);
}

TEST_F(ControlUnit16Test, ControlOpICategoryBranch) {

    uint16_t beq_op = 0xc;

    ControlOp cop = control_unit.control_op(beq_op);
    
    // Exec Jump
    ExecOp exec_op;
    exec_op.alu_src = 0;
    exec_op.reg_dst = 0;

    MemOp mem_op;
    mem_op.jmp = 0;
    mem_op.mem_write = 0;
    mem_op.mem_read = 0;
    mem_op.branch = 1;

    WriteOp write_op;
    write_op.mem_to_reg = 0;
    write_op.reg_write = 0;

    ControlOp control_op;
    control_op.exec_op = exec_op;
    control_op.mem_op = mem_op;
    control_op.write_op = write_op;
    
    //EXPECT_EQ(zero,cop);
    EXPECT_TRUE(control_op == cop);
}
