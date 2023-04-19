#include <iostream>
#include <timer.hpp>
#include <timecache.hpp>
#include <alarm.hpp>
#include <log.hpp>
#include <os.hpp>

#include <csignal>

void on_exit(int) {
	exit(0);
}

int main(int argc, char** argv){
	std::signal(SIGINT, on_exit);

	Timer time;
	TimeData data;
	TimeCache cache(".cache");
	
	Log log;

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
	
	OS::notify("timer:", "waiting to "+data.reason);	
	log.add("waiting to "+data.reason);

	while(!time.reach()){
		OS::clear();

		std::cout << "waiting to " << data.reason << "\n";
		std::cout << "waiting: " << data.end.pattern() << "\n";
		std::cout << "timer: " << time.current().pattern() << "\n\n";

		time.wait(1000);
	}
	
	OS::notify("timer:", "time to "+data.reason);
	log.add("time to "+data.reason);
	
	std::cout << "time reached\n";
	
	Alarm alarm = Alarm(".wav");
	
	while(true){
		alarm.play();
	}
	
	return 0;
}
