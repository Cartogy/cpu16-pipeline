#include <gtest/gtest.h>

#include "Memory/memory.hpp"

class MemoryTest : public ::testing::Test {
	protected:
		Memory m1;
		Memory m2;
	void SetUp() override {
		m1 = Memory();
		m2 = Memory(20);


		m1.store(0,20);
		m1.store(1,60);

		m2.store(0,1);
		m2.store(1,2);
	}
};

TEST_F(MemoryTest, Constructing) {
	EXPECT_EQ(m1.get_max_memory(), 65535);
	EXPECT_EQ(m2.get_max_memory(), 20);

}

TEST_F(MemoryTest, LoadStoreData) {
	EXPECT_EQ(m1.load(0),20);
	EXPECT_EQ(m1.load(1),60);
	EXPECT_EQ(m2.load(0),1);
	EXPECT_EQ(m2.load(1),2);
}

TEST_F(MemoryTest, ClearData) {

	m1.clear_memory();
	m2.clear_memory();
	for(int i = 0; i < m1.get_max_memory(); i++) {
		EXPECT_EQ(0,m1.load(i));	
	}

	for(int i = 0; i < m2.get_max_memory(); i++) {
		EXPECT_EQ(0,m2.load(i));	
	}

}
