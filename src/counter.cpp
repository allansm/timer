#include <counter.hpp>

void Counter::loop(){
	while(pause){
		#ifdef _WIN32
			Sleep(1000);
		#else
			usleep(1000 * 1000);
		#endif
	}
	
	this->start = Time().ms;
	
	#ifdef _WIN32
		Sleep(1000);
	#else
		usleep(1000 * 1000);
	#endif

	int time = Time().ms - this->start;
	this->time += time;

	this->loop();
}

void Counter::input_loop(){
	std::string x;
	getline(std::cin, x);

	this->tap();
	this->input();
}

void Counter::tap(){
	this->pause = this->pause ? false : true;
}

Counter::Counter(){
	this->start = Time().ms;

	loops.push_back(std::thread([this](){
		this->loop();		
	}));
}

Time Counter::current(){
	return {this->time};
}

void Counter::input(){
	this->loops.push_back(std::thread([this](){
		this->input_loop();		
	}));
}

bool Counter::paused(){
	return this->pause;
}

void Counter::wait(int ms){
	#ifdef _WIN32
		Sleep(ms);
	#else
		usleep(ms * 1000);
	#endif
}
