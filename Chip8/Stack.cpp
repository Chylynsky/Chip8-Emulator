#include "Stack.h"

namespace Chip8
{
	Stack Stack::instance{};

	Stack::Stack() : stackPointer{ stack }
	{

	}

	Stack& Stack::GetInstance()
	{
		return instance;
	}

	inline bool Stack::IsEmpty()
	{
		return (stackPointer == stack);
	}
	inline uint16_t Stack::Top()
	{
		return *stackPointer;
	}

	inline void Stack::Push(uint16_t value)
	{
		*(stackPointer++) = value;
	}

	inline void Stack::Pop()
	{
		stackPointer--;
	}
}