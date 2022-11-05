#include <timecache.hpp>

TimeCache::TimeCache(std::string filename){
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
