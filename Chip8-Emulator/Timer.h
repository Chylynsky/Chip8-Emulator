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
		// Time measuremet takes place on its own thread
		std::thread timerThread;
		// Callback functions that get called on Timer object tick
		std::vector<std::function<void(void)>> callbacks;
		// Time interval of the ticks
		std::chrono::microseconds period;
		// Controlls the execution
		std::atomic<bool> terminate;

		// Main Timer process
		void TimerProcess();

	public:

		explicit Timer(std::chrono::microseconds period);
		~Timer();

		// Start the Timer
		void Start();
		// Stop the Timer
		void Stop();
		// Add new Tick callback
		void AttachCallback(std::function<void(void)> callback);
	};
}