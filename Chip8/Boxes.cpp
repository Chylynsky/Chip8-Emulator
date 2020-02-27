#include "Boxes.h"

namespace GUI
{
	const std::string ErrorBox::TITLE{ "Error!" };

	ErrorBox::ErrorBox(const std::string& message)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, TITLE.c_str(), message.c_str(), nullptr);
	}

	const std::string WarningBox::TITLE{ "Warning!" };
	
	WarningBox::WarningBox(const std::string& message)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, TITLE.c_str(), message.c_str(), nullptr);
	}
}