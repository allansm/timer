#include <timer.hpp>

Timer::Timer(std::string pattern){
	this->start = Time().ms;
	this->time = {pattern};
}

Timer::Timer(int start){
	this->start = start;
}

Time Timer::current(){
	return {Time().ms - this->start};
}

Time Timer::started_time(){
	return {this->start};
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
