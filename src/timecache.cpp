#include <timecache.hpp>

TimeCache::TimeCache(std::string filename){
	const char* home = getenv("HOME");
	
	home = home ? home : getenv("USERPROFILE");
	chdir(home);
	
	struct stat info;
	
	if(stat("timer", &info) != 0){
		#if defined _WIN32	
			mkdir("timer");
		#else
			mkdir("timer", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		#endif
	}

	chdir("timer");

	this->filename = filename;
}

void TimeCache::store(Time time){
	std::ofstream out(this->filename.c_str());
	out << std::to_string(time.ms);
	out.close();
}

void TimeCache::write(TimeData data){
	std::ofstream out(this->filename.c_str());
	
	out << data.reason << "\n";
	out << std::to_string(data.start.ms) << "\n";
	out << std::to_string(data.end.ms) << "\n";

	out.close();
}

TimeData TimeCache::read(){
	TimeData data;

	std::ifstream in(this->filename.c_str());
	std::string line;

	if(in.good()){
		getline(in, line);
		data.reason = line;

		getline(in, line);
		data.start = Time(std::stoi(line));
		
		getline(in, line);
		data.end = Time(std::stoi(line));

		return data;
	}

	return {"", Time(-1), Time(-1)};
}

int TimeCache::ms(){
	std::string ret = "0";
	
	std::ifstream in(this->filename.c_str());
	
	if(in.good()){
		in >> ret;
	}

	in.close();

	return std::stoi(ret);
}
