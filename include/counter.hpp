#include <libs.hpp>

#include <iostream>
#include <thread>
#include <vector>

class Counter{
	int time = 0;
	int start;

	std::vector<std::thread> loops;

	bool pause = false;

	void loop();
	void input_loop();
	void tap();

	public:
		Counter();	
		Time current();

		void input();
		bool paused();
};
