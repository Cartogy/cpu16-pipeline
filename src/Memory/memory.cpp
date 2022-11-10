#include "memory.hpp"

Memory::Memory() {
	max_memory = DEFAULT_MEMORY;
	memory.reserve(max_memory);
	// Initialize variables of vector

	for(int i = 0; i < max_memory; i++){
		memory.push_back(0);
	}
}

Memory::Memory(uint16_t p_max_memory) {
	max_memory = p_max_memory;
	memory.reserve(max_memory);
	// Initialize variables of vector

	for(int i = 0; i < max_memory; i++){
		memory.push_back(0);
	}
}

void Memory::clear_memory(){
	for(int i = 0; i < memory.size(); i++) {
		memory[i] = 0;
	}
}

void Memory::store(uint16_t to_address, uint16_t value) {
	if (to_address >= max_memory) {
		std::cout << "Storing in inaccessible memory" << std::endl;
	} else {
		memory[to_address] = value;
	}
}

uint16_t Memory::load(uint16_t from_address) {
	if (from_address >= max_memory) {
		std::cout << "Loading from inaccessible memory" << std::endl;
		return 0;
	} else {
		return memory[from_address];
	}
}

const std::vector<uint16_t> Memory::get_memory() {
	return memory;
}

uint16_t Memory::get_max_memory() {
	return max_memory;
}
