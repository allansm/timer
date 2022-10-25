#include <iostream>

#include <timer.hpp>

int main(int argc, char** argv){
	std::string pattern;
	std::cout << "time in (h:m:s): ";
	
	getline(std::cin, pattern);
	
	std::cin.clear();
	fflush(stdin);
	
	Timer timer;
	std::string current = timer.current().pattern();

	while(current != pattern){
		std::cout << "waiting: " << pattern << "\n";
		std::cout << "timer: " << current << "\n\n";

		current = timer.current().pattern();
	}

	std::cout << "time reached\n";

	return 0;
}
