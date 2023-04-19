#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include <fstream>

class Alarm{
	std::string file;	
	Mix_Music * alarm = NULL;

	public:
		Alarm(std::string file);

		void play();
};
