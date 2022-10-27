#include <timer.hpp>

Timer::Timer(std::string pattern){	
	this->start = Time().ms;
	this->time = {pattern};
}

Time Timer::current(){	
	return {Time().ms - this->start};
}

bool Timer::reach(){
	return this->current().ms > this->time.ms;
}

void Timer::wait(int ms){
	#ifdef _WIN32
		Sleep(ms);
	#else
		usleep(ms * 1000);
	#endif
}
