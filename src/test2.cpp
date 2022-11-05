#include <counter.hpp>
#include <alarm.hpp>
#include <timecache.hpp>

int main(int argc, char** argv){
	std::string title = argv[1];

	Counter time(argv[2]);
	TimeCache cache(title);

	time.add(cache.ms());

	time.input();

	while(!time.reach()){
		#if defined _WIN32
			system("cls");
		#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
			system("clear");	 
		#elif defined (__APPLE__)
			system("clear");	
		#endif
			
		Time current = time.current();	
		std::cout << title << " " << current.pattern() << "\n";
		cache.store(current);

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
