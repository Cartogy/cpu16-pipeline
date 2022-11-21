#include <gtest/gtest.h>
#include "ALU/alu_16.hpp"

class ALUTest : public ::testing::Test {
    protected:
        ALU16 alu;
};

TEST_F(ALUTest, Add) {
    EXPECT_EQ(2, alu.compute(1, 1, ALU16Ops::ADD));
    EXPECT_EQ(4, alu.compute(2, 2, ALU16Ops::ADD));
    EXPECT_EQ(11, alu.compute(9, 2, ALU16Ops::ADD));
}

TEST_F(ALUTest, Sub) {
    EXPECT_EQ(2, alu.compute(4, 2, ALU16Ops::SUB));
    EXPECT_EQ(6, alu.compute(9, 3, ALU16Ops::SUB));
    EXPECT_EQ(7, alu.compute(9, 2, ALU16Ops::SUB));
}

TEST_F(ALUTest, Mul) {
    EXPECT_EQ(8, alu.compute(4, 2, ALU16Ops::MUL));
    EXPECT_EQ(6, alu.compute(3, 2, ALU16Ops::MUL));
    EXPECT_EQ(24, alu.compute(6, 4, ALU16Ops::MUL));
}

TEST_F(ALUTest, Div) {
    EXPECT_EQ(2, alu.compute(4, 2, ALU16Ops::DIV));
    EXPECT_EQ(6, alu.compute(12, 2, ALU16Ops::DIV));
    EXPECT_EQ(8, alu.compute(24, 3, ALU16Ops::DIV));
}

TEST(ALUConstrolTest, RCategories) {
    uint16_t add_ins = 0x4;
    uint16_t sub_ins = 0x5;
    uint16_t mul_ins = 0x6;
    uint16_t div_ins = 0x7;

    EXPECT_EQ(ALU16Ops::ADD,ALU16::alu_op(add_ins));
    EXPECT_EQ(ALU16Ops::SUB,ALU16::alu_op(sub_ins));
    EXPECT_EQ(ALU16Ops::MUL,ALU16::alu_op(mul_ins));
    EXPECT_EQ(ALU16Ops::DIV,ALU16::alu_op(div_ins));
}
