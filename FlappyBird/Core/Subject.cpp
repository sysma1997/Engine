#include "Subject.h"

void Subject::add(std::string name, Observer* observer) {
	this->observers[name] = observer;
}
void Subject::remove(std::string name) {
	this->observers.erase(name);
}

void Subject::notify(std::string name) {
	this->observers[name]->onNotify();
}