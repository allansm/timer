#include <iostream>

#include <timer.hpp>

int main(int argc, char** argv){
	Timer t({1,0,0});
	
	while(true){
		std::cout << t.current().pattern() << "\n";
	}

	return 0;
}
