#pragma once
#include <string>
#include "SDL.h"

namespace GUI
{
	struct ErrorBox
	{
	private:
		static const std::string TITLE;
	public:
		ErrorBox(const std::string& message);
	};

	struct WarningBox
	{
	private:
		static const std::string TITLE;
	public:
		WarningBox(const std::string& message);
	};
}