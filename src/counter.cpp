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
	
	while(true){	
		getline(std::cin, x);
		this->tap();
		this->input_callback(this);
	}
}

void Counter::tap(){
	this->pause = this->pause ? false : true;
}

Counter::Counter(std::string pattern){
	this->start = Time().ms;
	this->target = pattern;

	loops.push_back(std::thread([this](){
		this->loop();		
	}));
}

Time Counter::current(){
	return {this->time};
}

void Counter::add(int ms){
	this->time += ms;
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

bool Counter::reach(){
	return this->current().ms > Time(this->target).ms;
}
