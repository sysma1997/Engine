#include <iostream>
#include <conio.h>

#include "1_Pong/Pong.h"
#include "2_Flappy_Bird/FlappyBird.h"

using namespace std;

int main() {
	cout << "Welcome to engine tests.\n";

	while (true) {
		cout << "Select number to init project test:\n\n";
		cout << "1 - Pong\n";
		cout << "2 - Flappy Bird\n";
		cout << "10 - Exit\n";
		
		int option = 0;
		cin >> option;
		cout << '\n';

		if (option == 1)
			pong();
		else if (option == 2)
			flappyBird();
		else if (option == 10)
			break;

		system("cls");
	}

	cout << "Created by: SYSMA\n";

	return 0;
}