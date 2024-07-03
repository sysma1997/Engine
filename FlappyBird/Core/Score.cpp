#include "Score.h"

Score::Score() : points{ 0 }, bestPoints{ 0 } {}

void Score::increase() {
	points++;
}

int Score::getPoints() {
	return this->points;
}
int Score::getBestPoints() {
	return this->bestPoints;
}

void Score::onNotify(Score::Events type) {
	switch (type) {
	case Score::Events::INCREASE:
		this->increase();
		break;
	}
}