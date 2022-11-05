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

int TimeCache::ms(){
	std::string ret = "0";
	
	std::ifstream in(this->filename.c_str());
	
	if(in.good()){
		in >> ret;
	}

	in.close();

	return std::stoi(ret);
}
