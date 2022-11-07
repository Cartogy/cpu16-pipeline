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

