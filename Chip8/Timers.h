#pragma once
#include <chrono>
#include <thread>
#include <vector>
#include <cmath>
#include <functional>

namespace Chip8
{
	constexpr std::chrono::milliseconds PERIOD{ std::chrono::milliseconds(1000 / 60) };

	class Timer
	{
		std::thread timerThread;
		std::vector<std::function<void(void)>> callbacks;
		std::chrono::milliseconds period;
		bool terminate;

		void TimerProcess();

	public:

		Timer();
		explicit Timer(std::chrono::milliseconds period);
		~Timer();
		void AttachCallback(std::function<void(void)> callback);
	};
}