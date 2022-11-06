#include <time.hpp>

class Timer{
	Time time;
	
	int start;

	public:
		Timer(std::string pattern);
		Timer(int start);

		Time current();
		Time started_time();
		bool reach();
		void wait(int ms);
};
