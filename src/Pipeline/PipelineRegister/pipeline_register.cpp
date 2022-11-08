#include "pipeline_register.hpp"

bool PipelineRegister::is_valid() {
    return valid;
}
void PipelineRegister::set_valid(bool val) {
    valid = val;
}
