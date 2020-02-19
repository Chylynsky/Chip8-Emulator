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

	Timer::Timer(std::chrono::milliseconds period) : period{ period }, terminate{ true }
	{

	}

	Timer::Timer(std::chrono::milliseconds period, std::function<void(void)> callback) : period{ period }, terminate{ true }
	{
		callbacks.push_back(callback);
	}

	Timer::Timer(std::chrono::milliseconds period, std::initializer_list<std::function<void(void)>> callbacks) : 
		callbacks{ std::vector<std::function<void(void)>>(callbacks.size()) }, period { period }, terminate{ true }
	{
		std::move(callbacks.begin(), callbacks.end(), this->callbacks.begin());
	}

	Timer::~Timer()
	{
		terminate = true;

		if (timerThread.joinable())
			timerThread.join();
	}

	void Timer::Start()
	{
		if (terminate)
		{
			terminate = false;
			timerThread = std::thread(&Timer::TimerProcess, this);
		}
		else
			return;
	}

	void Timer::Stop()
	{
		if (!terminate)
		{
			terminate = true;

			if (timerThread.joinable())
				timerThread.join();
		}
		else
			return;
	}

	void Timer::AttachCallback(std::function<void(void)> callback)
	{
		callbacks.push_back(callback);
	}
}
