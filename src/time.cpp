#include <time.hpp>

std::string Time::pattern(){
	return std::to_string(hours)+":"+std::to_string(minutes)+":"+std::to_string(seconds);
}

Time::Time(std::string str){
	std::string a = str;
	std::string tmp = a.substr(0, a.find(":"));
	
	int h = std::stoi(tmp);
	
	a.erase(0, a.find(":")+1);
	
	tmp = a.substr(0, a.find(":"));
	
	int m = std::stoi(tmp);	

	a.erase(0, a.find(":")+1);
	
	int s = std::stoi(a);

	int ms = (h*60*60*1000) + (m*60*1000) + (s*1000);

	this->hours = h;
	this->minutes = m;
	this->seconds = s;
	this->ms = ms;
}

Time::Time(int h, int m, int s, int ms){
	this->hours = h;
	this->minutes = m;
	this->seconds = s;
	this->ms = ms;
}

Time::Time(int ms){
	int h = ((ms/1000)/60) / 60;
	int m = ((ms/1000)/60) - (h*60);
	int s = (ms/1000) - ((m*60)+(h*60*60));
	
	this->hours = h;
	this->minutes = m;
	this->seconds = s;
	this->ms = ms;
}

Time::Time(){
	struct timeval tp;
	gettimeofday(&tp, NULL);
	
	int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	
	int h = ((ms/1000)/60) / 60;
	int m = ((ms/1000)/60) - (h*60);
	int s = (ms/1000) - ((m*60)+(h*60*60));
	
	this->hours = h;
	this->minutes = m;
	this->seconds = s;
	this->ms = ms;
}
