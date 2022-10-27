#include <counter.hpp>

int main(int argc, char** argv){
	Counter counter;

	counter.input();	
	
	std::string title = argv[1];

	Time target(argv[2]);

	while(target.ms > counter.current().ms){
		if(!counter.paused())
			std::cout << title << " " << counter.current().pattern() << "\n";

		counter.wait();
	}

	std::cout << "time reached\n";
	
	exit(0);
}
