#include <timer.hpp>

Timer::Timer(std::string pattern){
	struct timeval tp;
	gettimeofday(&tp, NULL);
	
	this->start = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	this->time = {pattern};
}

Time Timer::current(){	
	struct timeval tp;
	gettimeofday(&tp, NULL);
	
	return {(tp.tv_sec * 1000 + tp.tv_usec / 1000) - this->start};
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
