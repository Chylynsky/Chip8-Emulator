#include "Timers.h"

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
	Timer::Timer() : period{ PERIOD }, timerThread{ &Timer::TimerProcess, this }, terminate{ false }
	{

	}
	Timer::Timer(std::chrono::milliseconds period) : period{ period }, timerThread{ &Timer::TimerProcess, this }, terminate{ false }
	{

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
