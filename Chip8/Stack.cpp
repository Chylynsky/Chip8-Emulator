#include "Stack.h"

namespace Chip8
{
	Stack Stack::instance{};

	Stack::Stack() : stackPointer{ memory }
	{
		
	}

	Stack& Stack::GetInstance()
	{
		return instance;
	}

	bool Stack::IsEmpty()
	{
		return (stackPointer == memory);
	}

	uint16_t Stack::Top()
	{
		return *(stackPointer - 1);
	}

	void Stack::Push(uint16_t value)
	{
		*stackPointer = value;
		stackPointer++;
	}

	void Stack::Pop()
	{
		if (!IsEmpty())
			stackPointer--;
	}
}