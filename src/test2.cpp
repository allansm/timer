#include <counter.hpp>
#include <alarm.hpp>

int main(int argc, char** argv){
	Counter time(argv[2]);

	time.input();	
	
	std::string title = argv[1];

	while(!time.reach()){
		if(!time.paused())
			std::cout << title << " " << time.current().pattern() << "\n";

		time.wait();
	}

	std::cout << "time reached\n";
	
	Alarm alarm(".wav");
	
	while(true){
		alarm.play();
	}
	
	exit(0);
}
