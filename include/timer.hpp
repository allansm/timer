#include <time.hpp>

#include <sys/time.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

class Timer{
	int start;

	public:
		Timer();
		
		Time current();
};
