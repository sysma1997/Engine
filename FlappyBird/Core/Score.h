#pragma once

#include "Observer.h"

class Score : public Observer {
private:
	int points;
	int bestPoints;

	void increase();

public:
	enum Events {
		INCREASE
	};

	Score();

	int getPoints();
	int getBestPoints();

	virtual void onNotify(Events type);
};