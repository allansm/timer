#include <time.hpp>

class Timer{
	Time time;
	
	int start;

	public:
		Timer(std::string pattern);
		
		Time current();
		bool reach();
		void wait(int ms);
};
