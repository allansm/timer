#include <counter.hpp>

int main(){
	Counter counter;

	counter.input();

	while(true){
		if(!counter.paused())
			std::cout << counter.current().pattern() << "\n";

		#ifdef _WIN32
			Sleep(1000);
		#else
			usleep(1000 * 1000);
		#endif	
	}

	return 0;
}
