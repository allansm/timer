#include <timer.hpp>

Timer::Timer(std::string pattern){
	struct timeval tp;
	gettimeofday(&tp, NULL);
	
	this->time = {pattern};	
}

Time Timer::current(){	
	struct timeval tp;
	gettimeofday(&tp, NULL);
	
	int curr = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	
	curr = curr - start;

	int h = ((curr/1000)/60) / 60;
	int m = ((curr/1000)/60) - (h*60);
	int s = (curr/1000) - ((m*60)+(h*60*60));

	return {h, m, s, curr};
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
