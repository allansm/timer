#include <iostream>
#include <timer.hpp>

int main(int argc, char** argv){
	std::string pattern;
	std::cout << "time in (h:m:s): ";
	
	getline(std::cin, pattern);
	
	std::cin.clear();
	fflush(stdin);
	
	std::string reason;
	std::cout << "waiting to ";
	
	getline(std::cin, reason);
	
	std::cin.clear();
	fflush(stdin);
	
	Timer time(pattern);

	while(!time.reach()){
		std::cout << "waiting: " << pattern << "\n";
		std::cout << "timer: " << time.current().pattern() << "\n\n";

		time.wait(1000);
	}

	std::cout << "time reached\n";

	return 0;
}
