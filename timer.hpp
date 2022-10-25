#include "time.hpp"

#include <sys/time.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

class Timer{
	std::string pattern;

	int start;

	public:
		Timer(std::string pattern);
		
		Time current();
};
