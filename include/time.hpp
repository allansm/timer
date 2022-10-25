#include <string>

struct Time{
	int hours;
	int minutes;
	int seconds;
	int ms;

	std::string pattern(){
		return std::to_string(hours)+":"+std::to_string(minutes)+":"+std::to_string(seconds);
	}
};
