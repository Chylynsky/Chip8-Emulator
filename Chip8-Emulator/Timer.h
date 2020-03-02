#pragma once
#include <chrono>
#include <thread>
#include <vector>
#include <atomic>
#include <functional>

namespace Chip8
{
	class Timer
	{
		std::thread timerThread;
		std::vector<std::function<void(void)>> callbacks;
		std::chrono::microseconds period;
		std::atomic<bool> terminate;

		void TimerProcess();

	public:

		explicit Timer(std::chrono::microseconds period);
		~Timer();

		void Start();
		void Stop();
		void AttachCallback(std::function<void(void)> callback);
	};
}