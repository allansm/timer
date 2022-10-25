#include <iostream>
#include <timer.hpp>

int main(int argc, char** argv){
	std::string pattern;
	std::cout << "time in (h:m:s): ";
	
	getline(std::cin, pattern);
	
	std::cin.clear();
	fflush(stdin);
	
	Timer time(pattern);

	while(!time.reach()){
		std::cout << "waiting: " << pattern << "\n";
		std::cout << "timer: " << time.current().pattern() << "\n\n";
	}

	std::cout << "time reached\n";

	return 0;
}
