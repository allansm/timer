#include <counter.hpp>

int main(int argc, char** argv){
	Counter counter;

	counter.input();	
	Time test = (std::string)"0:0:10";
	while(counter.current().ms < test.ms){
		if(!counter.paused())
			std::cout << counter.current().pattern() << "\n";

		counter.wait();
	}

	std::cout << "time reached\n";
	
	exit(0);
}
