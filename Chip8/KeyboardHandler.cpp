#include "KeyboardHandler.h"

Chip8::KeyboardHandler::KeyboardHandler() : keyCode{ 0x0 }, isAnyKeyPressed{ false }
{
}

Chip8::KeyboardHandler::~KeyboardHandler()
{
}

void Chip8::KeyboardHandler::NoKeyPressed()
{
	std::lock_guard<std::mutex> keyboardHandlerGuard{ keyboardHandlerMutex };
	isAnyKeyPressed = false;
}

void Chip8::KeyboardHandler::KeyPressed(uint8_t keyCode)
{
	std::lock_guard<std::mutex> keyboardHandlerGuard{ keyboardHandlerMutex };
	isAnyKeyPressed = true;
	this->keyCode = keyCode;
}

bool Chip8::KeyboardHandler::IsAnyKeyPressed()
{
	std::lock_guard<std::mutex> keyboardHandlerGuard{ keyboardHandlerMutex };
	return isAnyKeyPressed;
}

uint8_t Chip8::KeyboardHandler::GetPressedKeyCode()
{
	std::lock_guard<std::mutex> keyboardHandlerGuard{ keyboardHandlerMutex };
	if (!isAnyKeyPressed)
		throw std::runtime_error("No key pressed.");
	else
	{
#ifdef _DEBUG
		std::cout << "Key pressed: " << static_cast<short>(keyCode) << std::endl;
#endif
		return keyCode;
	}
}
