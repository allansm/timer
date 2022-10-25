#include <iostream>
#include <sys/time.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

struct Time{
	int h;
	int m;
	int s;

	std::string pattern(){
		return std::to_string(h)+":"+std::to_string(m)+":"+std::to_string(s);
	}
};

class Timer{
	Time time;
	int start;	

	public:
		Timer(Time time){
			this->time = time;

			struct timeval tp;
			gettimeofday(&tp, NULL);
			
			this->start = tp.tv_sec * 1000 + tp.tv_usec / 1000;
		}

		Time current(){	
			#ifdef _WIN32
				Sleep(1000);
			#else
				usleep(1000 * 1000);
			#endif

			struct timeval tp;
			gettimeofday(&tp, NULL);
			
			int curr = tp.tv_sec * 1000 + tp.tv_usec / 1000;
			
			curr = curr - start;

			int h = ((curr/1000)/60) / 60;
			int m = ((curr/1000)/60) - (h*60);
			int s = (curr/1000) - ((m*60)+(h*60*60));

			return {h, m, s};
		}
};

int main(int argc, char** argv){
	Timer t({1,0,0});
	
	while(true){
		std::cout << t.current().pattern() << "\n";
	}

	return 0;
}
