#include <iostream>
#include <timer.hpp>
#include <timecache.hpp>
#include <alarm.hpp>
#include <log.hpp>

int main(int argc, char** argv){
	Timer time;
	TimeData data;
	TimeCache cache(".cache");
	Log log;

	std::string command = "";

	if(argc == 1){
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

		time = Timer(pattern);
		
		data = time.data();
		data.reason = reason;

		cache.write(data);	
	}else if((std::string)argv[1] == "continue"){
		data = cache.read();

		time = Timer(data.start.ms, data.end.ms);
		
		if(data.start.ms == -1){
			std::cout << "no cached time\n";

			return 0;
		}
	}else{
		return 0;
	}

	#if defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
		command = "notify-send timer: \"waiting to "+data.reason+"\"";
		
		system(command.c_str());
	#endif
	
	log.add("waiting to "+data.reason);

	while(!time.reach()){
		#if defined _WIN32
			system("cls");
		#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
			system("clear");	 
		#elif defined (__APPLE__)
			system("clear");	
		#endif

		std::cout << "waiting to " << data.reason << "\n";
		std::cout << "waiting: " << data.end.pattern() << "\n";
		std::cout << "timer: " << time.current().pattern() << "\n\n";

		time.wait(1000);
	}
	
	#if defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
		command = "notify-send timer: \"time to "+data.reason+"\"";
		
		system(command.c_str());
	#endif
	
	log.add("time to "+data.reason);
	
	std::cout << "time reached\n";
	
	Alarm alarm(".wav");
	
	while(true){
		alarm.play();
	}

	return 0;
}
