#include <after.hpp>

After::After(std::string pattern, void(*action)()){
	this->action = action;
	this->pattern = pattern;
	this->timer = Timer(pattern);
}

bool After::exec(){
	bool result = false;

	if(timer.reach()){
		result = true;

		this->action();
		timer = Timer(this->pattern);
	}

	return result;
}
