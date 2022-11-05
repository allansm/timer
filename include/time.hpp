#ifndef TIME
#define TIME

#include <libs.hpp>

class Time{	
	public:
		int hours;
		int minutes;
		int seconds;
		int ms;

		std::string pattern();		
		
		Time(std::string str);
		Time(int h, int m, int s, int ms);
		Time(int ms);
		Time();
};

#endif
