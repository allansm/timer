#include <os.hpp>

OS::OS(){

}

void OS::notify(std::string title, std::string message){
	std::string command = "";

	#if defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
		command = "notify-send \""+title+"\" \""+message+"\"";
		
		system(command.c_str());
	#endif
}

void OS::clear(){
	#if defined _WIN32
		system("cls");
	#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
		system("clear");	 
	#elif defined (__APPLE__)
		system("clear");	
	#endif
}

