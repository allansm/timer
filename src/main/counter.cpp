#include <counter.hpp>
#include <alarm.hpp>
#include <timecache.hpp>
#include <log.hpp>
#include <os.hpp>

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

	time.add(cache.ms());
	
	time.input_callback = [](auto time){
		Log log;
		Time current = time->current();
		std::string command = "";

		if(time->paused()){
			OS::notify(title, current.pattern()+" paused");
			log.add(title+" "+current.pattern()+" paused");
		}else{
			OS::notify(title, current.pattern()+" started");
			log.add(title+" "+current.pattern()+" started");
		}
	};

	time.input();

	OS::notify(title, time.current().pattern()+" started");
	log.add(title+" "+time.current().pattern()+" started");

	while(!time.reach()){
		OS::clear();

		Time current = time.current();
		std::cout << title << " " << current.pattern() << "\n";
		cache.store(current);

		if(time.paused())
			std::cout << "paused\n";

		time.wait();
	}	

	OS::notify("counter", "time reached");
	log.add(title+" time reached");
	
	std::cout << "time reached\n";
	
	Alarm alarm(".wav");
	
	while(true){
		alarm.play();	
	}
	
	exit(0);
}
