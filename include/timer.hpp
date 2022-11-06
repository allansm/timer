#include <timedata.hpp>

class Timer{
	Time time;
	
	int start;

	public:
		Timer(){
		}

		Timer(std::string pattern);
		Timer(int start, int end);

		Time current();
		TimeData data();
		bool reach();
		void wait(int ms);
};
