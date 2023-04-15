#include <alarm.hpp>

Alarm::Alarm(std::string file){
	if(!std::ifstream(file.c_str()).good()){
		this->file = file;	

		auto little = [](std::vector<int>& bytes, int value, int size){
			while(size){
				bytes.push_back(value & 0xFF);
				value = value >> 8;
				
				size-=1;
			}	
		};
		
		std::vector<int> bytes = {
			'R', 'I', 'F', 'F',
			 0,   0,   0,   0,
			'W', 'A', 'V', 'E',
			'f', 'm', 't', ' '
		};

		little(bytes, 16, 4);
		little(bytes, 1, 2);
		little(bytes, 2, 2);
		little(bytes, 44100, 4);
		little(bytes, 44100 * 16 * 2 / 8, 4);
		little(bytes, 4, 2);
		little(bytes, 16, 2);
		
		for(int b : {'d', 'a', 't', 'a'}){
			bytes.push_back(b);
		}

		std::vector<int> data;

		int N = 44100 * 0.03;
		for(int n = 0;n < N;n++){
			little(data, (int)(((double) n / N * 32760)  * 75), 2);
			little(data, (int)(((32760) - ((double) n / N * 32760)) * 75), 2);	
		}

		N = 44100 * 0.12;
		for(int n = 0;n < N;n++){
			little(data, (int)(((double) n / N * 0)  * 1), 2);
			little(data, (int)((0 - ((double) n / N * 0)) * 1), 2);
		}

		little(bytes, data.size(), 4);

		for(auto b : data){
			bytes.push_back(b);
		}

		int tmp = bytes.size();
		
		data[4] = tmp & 0xFF;

		tmp = tmp >> 8;
		data[5] = tmp & 0xFF;

		tmp = tmp >> 8;
		data[6] = tmp & 0xFF;

		tmp = tmp >> 8;
		data[7] = tmp & 0xFF;
		
		std::ofstream wav(this->file.c_str());
		
		for(char b : bytes){
			wav << b;
		}

		wav.close();
	}
}

void Alarm::play(){
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Music *music = Mix_LoadMUS(this->file.c_str());
	Mix_PlayMusic(music, 1);

	while(Mix_PlayingMusic()){
		SDL_Delay(250);
	}

	Mix_FreeMusic(music);
	Mix_CloseAudio();
	SDL_Quit();
}
