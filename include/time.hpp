#include <string>

struct Time{
	int h;
	int m;
	int s;
	int ms;

	std::string pattern(){
		return std::to_string(h)+":"+std::to_string(m)+":"+std::to_string(s);
	}
};
