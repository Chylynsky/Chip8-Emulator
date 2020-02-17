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

	Timer::Timer(std::chrono::milliseconds period) : timerThread{ &Timer::TimerProcess, this }, period{ period }, value{ 0 }, terminate{ false }
	{
	}

	Timer::Timer(std::chrono::milliseconds period, std::function<void(void)> callback) : timerThread{ &Timer::TimerProcess, this }, period{ period }, value{ 0 }, terminate{ false }
	{
		callbacks.push_back(callback);
	}

	Timer::~Timer()
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
