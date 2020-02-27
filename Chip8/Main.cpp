#include "Application.h"

#include "AudioFile.h"
#include <iostream>

int main(int argc, char* argv[])
{
	/*Chip8::Application app;
	app.Run();*/
	SDL_Init(SDL_INIT_AUDIO);
	Chip8::AudioFile f{ "Resources/tone.wav" };

	char c = 0;
	while (c != 'e')
	{
		std::cin >> c;

		if (c == 'p')
			f.Play();
		else if (c == 's')
			f.Pause();
	}

	return 0;
}