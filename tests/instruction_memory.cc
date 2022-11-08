#include <gtest/gtest.h>

#include "InstructionMemory/instruction_memory.hpp"

class InstructionMemoryTest : public ::testing::Test {
	protected:
		InstructionMemory<uint16_t> ins_mem;
	
	void SetUp() override {
		ins_mem = InstructionMemory<uint16_t>();
	}
};

TEST_F(InstructionMemoryTest, Constructing) {
	EXPECT_EQ(0, ins_mem.total_instructions());
}

TEST_F(InstructionMemoryTest, InstructionManipulation) {
	ins_mem.add_instruction(1);
	ins_mem.add_instruction(10);

	// Ensure 2 instructions are present
	ASSERT_EQ(2, ins_mem.total_instructions());

	EXPECT_EQ(1, ins_mem.get_instruction(0));
	EXPECT_EQ(10, ins_mem.get_instruction(1));

	ins_mem.clear();

	ASSERT_EQ(0, ins_mem.total_instructions());
}
