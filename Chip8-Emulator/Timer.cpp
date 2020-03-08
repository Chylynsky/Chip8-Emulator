#include "Timer.h"

namespace Chip8
{
	void Timer::TimerProcess()
	{
		// Process continues untill terminate is true
		while (!terminate.load())
		{
			// Wait for the specified period
			std::this_thread::sleep_for(period);

			// Call the callbacks
			for (std::function<void(void)> callback : callbacks)
				callback();
		}
	}

	Timer::Timer(std::chrono::microseconds period) : period{ period }
	{
		terminate.store(true);
	}

	Timer::~Timer()
	{
		terminate.store(true);

		if (timerThread.joinable())
			timerThread.join();
	}

	void Timer::Start()
	{
		terminate.store(false);
		// Start new Timer thread
		timerThread = std::thread(&Timer::TimerProcess, this);
	}

	void Timer::Stop()
	{
		// Terminate the process
		terminate.store(true);

		if (timerThread.joinable())
			timerThread.join();
	}

	void Timer::AttachCallback(std::function<void(void)> callback)
	{
		// Add new function to the std::vector of callbacks
		callbacks.push_back(callback);
	}
}
