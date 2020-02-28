#include "Timer.h"

namespace Chip8
{
	void Timer::TimerProcess()
	{
		while (!terminate.load())
		{
			std::this_thread::sleep_for(period);

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
		timerThread = std::thread(&Timer::TimerProcess, this);
	}

	void Timer::Stop()
	{
		terminate.store(true);

		if (timerThread.joinable())
			timerThread.join();
	}

	void Timer::AttachCallback(std::function<void(void)> callback)
	{
		callbacks.push_back(callback);
	}
}
