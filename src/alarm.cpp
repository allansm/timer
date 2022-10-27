#include <alarm.hpp>

Alarm::Alarm(std::string file){
	this->file = file;
}

void Alarm::play(){
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	Mix_Music *music = Mix_LoadMUS(this->file.c_str());
	Mix_PlayMusic(music, 1);

	while(Mix_PlayingMusic()){
		SDL_Delay(250);
	}

	Mix_FreeMusic(music);
	Mix_CloseAudio();
}
