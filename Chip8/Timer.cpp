#include "Timer.h"

namespace Chip8
{
	void Timer::TimerProcess()
	{
		while (!terminate)
		{
			std::this_thread::sleep_for(period);

			for (std::function<void(void)> callback : callbacks)
				callback();
		}
	}

	Timer::Timer(std::chrono::microseconds period) : period{ period }, terminate{ true }
	{
	}

	Timer::~Timer()
	{
		terminate = true;

		if (timerThread.joinable())
			timerThread.join();
	}

	void Timer::Start()
	{
		terminate = false;
		timerThread = std::thread(&Timer::TimerProcess, this);
	}

	void Timer::Stop()
	{
		terminate = true;

		if (timerThread.joinable())
			timerThread.join();
	}

	void Timer::AttachCallback(std::function<void(void)> callback)
	{
		callbacks.push_back(callback);
	}
}
