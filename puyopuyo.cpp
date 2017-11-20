//
// Created by John on 2017-11-17.
//

#include <iostream>

#include "algorithm.h"
#include "ui.h"

using namespace std;

int main() {
	int option;
	cout << "1: start game" << endl;
	cout << "2: view rank" << endl;
	cout << "-1: end" << endl;
	cout << "input: " << endl;
	cin >> option;
	system("CLS");
	if (option == 1) {
		cout << "Easy stage 1~3" << endl;
		cout << "Expert stage 4~6" << endl;
		cout << "Select stage: " << endl;
		cin >> option;
		Blocks stage(option); // 블록들을 file에서 읽어온다
	}
	else if (option == 2) {
		
	}
	else if (option == -1) {
		cout << "Bye Bye" << endl;
		return 0;
	}
	else {
		cout << "*** Wrong Input!! ***" << endl;
	}
	return 0;

}



