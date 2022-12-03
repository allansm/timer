#include <timer.hpp>

class After{
	Timer timer;
	std::string pattern;
	void (*action)() = [](){};
	
	public:
		After(std::string pattern, void(*action)());
		bool exec();
};
