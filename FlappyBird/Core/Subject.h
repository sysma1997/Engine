#pragma once

#include <string>
#include <map>

#include "Observer.h"

class Subject {
private:
	std::map<std::string, Observer*> observers;

public:
	void add(std::string name, Observer* observer);
	void remove(std::string name);

protected:
	void notify(std::string name);
};