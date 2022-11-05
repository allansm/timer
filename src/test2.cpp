#include <counter.hpp>
#include <alarm.hpp>

int main(int argc, char** argv){
	Counter time(argv[2]);

	time.input();	
	
	std::string title = argv[1];

	while(!time.reach()){
		#if defined _WIN32
			system("cls");
		#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
			system("clear");	 
		#elif defined (__APPLE__)
			system("clear");	
		#endif
		
		std::cout << title << " " << time.current().pattern() << "\n";
		
		if(time.paused())
			std::cout << "paused\n";

		time.wait();
	}

	std::cout << "time reached\n";
	
	Alarm alarm(".wav");
	
	while(true){
		alarm.play();
	}
	
	exit(0);
}
