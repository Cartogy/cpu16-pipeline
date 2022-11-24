#ifndef MEMORY
#include <vector>
#include <iostream>
#define MEMORY

#define DEFAULT_MEMORY 65535

class Memory {
	private:
		std::vector<uint16_t> memory;
		uint16_t max_memory;

	public:
		Memory(uint16_t p_max_memory);
		Memory();

		void clear_memory();
		void store(uint16_t to_address, uint16_t value);
		uint16_t load(uint16_t from_address);
		const std::vector<uint16_t> get_memory();
		uint16_t get_max_memory();

};
#endif
