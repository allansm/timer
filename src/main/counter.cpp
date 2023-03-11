#include <counter.hpp>
#include <alarm.hpp>
#include <timecache.hpp>
#include <log.hpp>
#include <os.hpp>
#include <after.hpp>

std::string title = "";
Time current;

int main(int argc, char** argv){
	if(argc < 2){
		std::cout << "usage: counter [ title ] [ time: hh:mm:ss ]\n";

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
	
	Log log;

	After cache("0:1:0", [](){
		Log log(title+".log");
		TimeCache cache(title);

		log.add(title+" "+current.pattern());
		cache.store(current);
	});

	time.add(TimeCache(title).ms());
	
	time.input_callback = [](auto time){
		Log log;
		Time current = time->current();

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

		current = time.current();
		std::cout << title << " " << current.pattern() << "\n";
		
		cache.exec();

		if(time.paused()){
			std::cout << "paused\n";
			
			Alarm alarm(".wav");
			alarm.play();

			time.wait(10000);
		}else{
			time.wait();
		}
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
