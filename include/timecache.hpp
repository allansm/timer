#include <time.hpp>
#include <fstream>

class TimeCache{
	std::string filename;

	public:
		TimeCache(std::string filename);
		void store(Time time);
		int ms();
};
