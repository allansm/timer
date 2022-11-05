#include <time.hpp>

#include <iostream>
#include <thread>
#include <vector>

class Counter{
	int time = 0;
	int start;

	std::vector<std::thread> loops;

	bool pause = false;

	std::string target;

	void loop();
	void input_loop();
	void tap();

	public:
		Counter(std::string pattern);
		Time current();

		void add(int ms);
		void input();
		bool paused();
		void wait(int ms=1000);
		bool reach();
};
