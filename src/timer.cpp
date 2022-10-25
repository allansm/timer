#include <timer.hpp>

Timer::Timer(std::string pattern){
	struct timeval tp;
	gettimeofday(&tp, NULL);

	this->start = tp.tv_sec * 1000 + tp.tv_usec / 1000;

	std::string tmp = pattern.substr(0, pattern.find(":"));
	
	int h = std::stoi(tmp);
	
	pattern.erase(0, pattern.find(":")+1);
	
	tmp = pattern.substr(0, pattern.find(":"));
	
	int m = std::stoi(tmp);	

	pattern.erase(0, pattern.find(":")+1);
	
	int s = std::stoi(pattern);

	int ms = (h*60*60*1000) + (m*60*1000) + (s*1000);

	this->time = {h, m, s, ms};
}

Time Timer::current(){
	#ifdef _WIN32
		Sleep(1000);
	#else
		usleep(1000 * 1000);
	#endif

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
