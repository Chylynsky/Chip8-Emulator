#pragma once
#include <cstdint>
#include <chrono>
#include <initializer_list>
#include <thread>
#include <vector>
#include <atomic>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>

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