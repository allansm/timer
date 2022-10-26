#include <time.hpp>
#include <sys/time.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#include <iostream>

class Timer2{
	int time = 0;
	int start;

	public:
		Timer2(int time=0){
			this->time = time;

			struct timeval tp;
			gettimeofday(&tp, NULL);

			start = tp.tv_sec * 1000 + tp.tv_usec / 1000;
		}
		
		Time add(int ms=1000){
			struct timeval tp;
			gettimeofday(&tp, NULL);
			this->start = tp.tv_sec * 1000 + tp.tv_usec / 1000;
			
			#ifdef _WIN32
				Sleep(ms);
			#else
				usleep(ms * 1000);
			#endif

			gettimeofday(&tp, NULL);

			int time = tp.tv_sec * 1000 + tp.tv_usec / 1000 - this->start;
			this->time += time;

			int h = ((this->time/1000)/60) / 60;
			int m = ((this->time/1000)/60) - (h*60);
			int s = (this->time/1000) - ((m*60)+(h*60*60));

			return {h, m, s, this->time};
		}
};

main(){
	Timer2 t;

	while(true){
		Time current = t.add(1000);

		std::cout << current.pattern() << "\n";

		if(current.ms % 2 == 0){
			std::cout << "paused\n\n";
			
			usleep(1000*1000);
		}
	}
}
