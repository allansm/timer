#include <time.hpp>
#include <fstream>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

class TimeCache{
	std::string filename;

	public:
		TimeCache(std::string filename);
		void store(Time time);
		int ms();
};
