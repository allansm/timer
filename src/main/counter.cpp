#include <counter.hpp>
#include <alarm.hpp>
#include <timecache.hpp>

int main(int argc, char** argv){
	if(argc < 2){
		std::cout << "usage: test2 [ title ] [ time: hh:mm:ss ]\n";

		return 0;
	}

	std::string title = argv[1];
	
	if(title == "@"){
		time_t now = time(0);
		tm *ltm = localtime(&now);
		
		int d = ltm->tm_mday;
		int m = ltm->tm_mon+1;
		int y = ltm->tm_year+1900;

		title = std::to_string(d);
		title += std::to_string(m);
		title += std::to_string(y);
	}

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
