#include <gtest/gtest.h>
#include "PipelineRegister/pipeline_register.hpp"

class PipelineTest : public ::testing::Test {
    protected:
        PipelineRegister pg;
};

class CustomRegTest : public ::testing::Test {
    protected:
        IfDecReg<uint16_t> ifdec_reg;
        DecExecReg<uint16_t, uint16_t> decexec_reg;
        ExecMemReg<uint16_t, uint16_t> execmem_reg;
        MemWriteReg<uint16_t, uint16_t> memwrite_reg;
        UpdateArch<uint16_t, uint16_t> update_arch;
};

TEST_F(PipelineTest, BasicPipeline) {
    pg.set_valid(true);
    EXPECT_TRUE(pg.is_valid());
    pg.set_valid(false);
    EXPECT_FALSE(pg.is_valid());
}

IfDecReg<uint16_t> mutate_ifdec(IfDecReg<uint16_t> r) {
    r.instruction += 1;

    return r;
}

/** Test the Copy functionality **/
TEST_F(CustomRegTest, BehaviourTest) {
    ifdec_reg.instruction = 5;
    IfDecReg<uint16_t> new_reg = mutate_ifdec(ifdec_reg);
    IfDecReg<uint16_t> new_reg_two = mutate_ifdec(ifdec_reg);

    EXPECT_NE(ifdec_reg.instruction, new_reg.instruction);
    EXPECT_EQ(new_reg_two.instruction, new_reg.instruction);
}
