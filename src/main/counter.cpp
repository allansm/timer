#include <counter.hpp>
#include <alarm.hpp>
#include <timecache.hpp>
#include <log.hpp>

std::string title = "";

int main(int argc, char** argv){
	if(argc < 2){
		std::cout << "usage: test2 [ title ] [ time: hh:mm:ss ]\n";

		return 0;
	}

	title = argv[1];
	
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
	
	Log log;
	std::string command = "";

	time.add(cache.ms());
	
	time.input_callback = [](auto time){
		Log log;
		Time current = time->current();
		std::string command = "";

		if(time->paused()){
			#if defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
				command = "notify-send counter: \""+title+" "+current.pattern()+" paused\"";
				system(command.c_str());
			#endif

			log.add(title+" "+current.pattern()+" paused");
		}else{
			#if defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
				command = "notify-send counter: \""+title+" "+current.pattern()+" started\"";
				system(command.c_str());
			#endif

			log.add(title+" "+current.pattern()+" started");
		}
	};
	time.input();

	#if defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
		command = "notify-send counter: \""+title+" "+time.current().pattern()+" started\"";
		system(command.c_str());
	#endif

	log.add(title+" "+time.current().pattern()+" started");

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
	
	#if defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
		system("notify-send counter: \"time reached\"");
	#endif

	log.add(title+" time reached");
	
	std::cout << "time reached\n";
	
	Alarm alarm(".wav");
	
	while(true){
		alarm.play();
	}
	
	exit(0);
}
