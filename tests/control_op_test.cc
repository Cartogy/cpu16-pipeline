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

TEST_F(ControlUnit16Test, ControlOpZero) {
    ControlOp cop = control_unit.control_op(0);
    
    EXPECT_EQ(zero,cop);
}
