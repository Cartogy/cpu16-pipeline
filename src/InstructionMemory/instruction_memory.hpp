#ifndef INSTRUCTION_MEMORY
#define INSTRUCTION_MEMORY

#include <vector>
#include <iostream>

#define _MAX_INSTRUCTIONS 256

template <typename T>
class InstructionMemory {
	private:
		std::vector<T> instruction_memory;
	public:
		InstructionMemory();
		T get_instruction(size_t index);
		void add_instruction(T ins);
		size_t total_instructions();
		void clear();
};

/* Include in Header to avoid having to initialize all the possible instruction types */

template <typename T>
InstructionMemory<T>::InstructionMemory() {
	instruction_memory.reserve(_MAX_INSTRUCTIONS);
}

//TODO: Has no Error Checking!
template <typename T>
T InstructionMemory<T>::get_instruction(size_t index){
	return instruction_memory[index];
}

template <typename T>
void InstructionMemory<T>::add_instruction(T ins) {
	instruction_memory.push_back(ins);
}

template <typename T>
size_t InstructionMemory<T>::total_instructions() {
	return instruction_memory.size();
}

template <typename T>
void InstructionMemory<T>::clear() {
	instruction_memory.clear();
}

#endif
