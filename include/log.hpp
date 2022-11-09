#include <fstream>
#include <string>

class Log{
	std::string filename = ".log";

	public:
		Log();
		Log(std::string filename);

		void add(std::string text);
};
