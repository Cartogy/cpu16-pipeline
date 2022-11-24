#include <gtest/gtest.h>
#include "StateElements/state_elements.hpp"

class StateElementsTest : public ::testing::Test {
    protected:
        StateElements se;
};

TEST_F(StateElementsTest, InstructionTest) {
    se.set_instruction(2);
    EXPECT_EQ(2, se.get_current_instruction());
    se.set_instruction(6);
    EXPECT_EQ(6, se.get_current_instruction());
}

TEST_F(StateElementsTest, RegisterTest) {
    se.set_register_value(0, 1);
    se.set_register_value(1, 2);

    EXPECT_EQ(1, se.get_register_value(0));
    EXPECT_EQ(2, se.get_register_value(1));
}

TEST_F(StateElementsTest, ProgramCounterTest) {
    se.set_program_counter(0);
    EXPECT_EQ(0,se.get_program_counter());
    se.set_program_counter(4);
    EXPECT_EQ(4, se.get_program_counter());
}
