#include <string>

class OS{	
	public:
		OS();
		
		static void notify(std::string title, std::string message);
		static void clear();
};
