#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include <fstream>

class Alarm{
	std::string file;	

	public:
		Alarm(std::string file);
		
		void play();
};
