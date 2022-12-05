#include <gtest/gtest.h>
#include "Emulator/emulator.hpp"

class EmulatorTest : public ::testing::Test {
    protected:
        Emulator emu;
        uint16_t add_ins = 0x4012;
        uint16_t sub_ins = 0x5012;

        std::vector<uint16_t> instructions;

        void SetUp() override {
            instructions.push_back(add_ins);
            instructions.push_back(sub_ins);
        }
};

TEST_F(EmulatorTest, EmulatorTestAddInstructions) {
    emu.add_instructions(instructions); 

    ASSERT_EQ(2, emu.total_instructions());
}

TEST_F(EmulatorTest, EmulatorTestClockCycleOne) {
    emu.add_instructions(instructions);

    emu.execute_clock_cycle();

    ASSERT_TRUE(emu.valid_ifdec_reg());

    const IfDecReg<uint16_t>& ifdec_reg = emu.get_ifdec_reg();
    EXPECT_EQ(add_ins,ifdec_reg.instruction);
    EXPECT_EQ(1,ifdec_reg.pc_increment);
}
