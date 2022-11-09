#include <log.hpp>
#include <sys/time.h>

Log::Log(){

}

Log::Log(std::string filename){
	this->filename = filename;
}

void Log::add(std::string text){
	std::string date = "";
	time_t now = time(0);
	tm *ltm = localtime(&now);
	
	int d = ltm->tm_mday;
	int m = ltm->tm_mon+1;
	int y = ltm->tm_year+1900;
	int h = ltm->tm_hour;
	int mi = ltm->tm_min;

	date = std::to_string(d)+"/";
	date += std::to_string(m)+"/";
	date += std::to_string(y)+" ";
	date += std::to_string(h)+":";
	date += std::to_string(mi);
	
	std::ofstream log(this->filename.c_str(), log.out | log.app);

	log << text << " " << date <<"\n";

	log.close();
}
