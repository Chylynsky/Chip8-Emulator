#pragma once
#include <cstdint>
#include <chrono>
#include <thread>
#include <vector>
#include <cmath>
#include <functional>

namespace Chip8
{
	class Timer
	{
		std::thread timerThread;
		std::vector<std::function<void(void)>> callbacks;
		std::chrono::milliseconds period;
		uint8_t value;
		bool terminate;

		void TimerProcess();

	public:

		explicit Timer(std::chrono::milliseconds period);
		Timer(std::chrono::milliseconds period, std::function<void(void)> callback);
		~Timer();

		void AttachCallback(std::function<void(void)> callback);
	};
}