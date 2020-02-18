#pragma once
#include <cstdint>

namespace Chip8
{
	class Stack
	{
		static constexpr uint16_t STACK_SIZE{ 16 };

		static Stack instance;

		uint16_t memory[STACK_SIZE];
		uint16_t* stackPointer;

		Stack();

	public:

		static Stack& GetInstance();
		bool IsEmpty();
		uint16_t Top();
		void Push(uint16_t value);
		void Pop();

		Stack& operator=(const Stack&) = delete;
		Stack& operator=(Stack&&) = delete;
	};
}