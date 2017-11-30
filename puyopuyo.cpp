//
// Created by John on 2017-11-17.
//

#include <iostream>
#include <windows.h>

#include "algorithm.h"
#include "ui.h"

using namespace std;

int main() {
	char inst;
	while (1) {
		string option;
		cout << "1: start game" << endl;
		cout << "2: view rank" << endl;
		cout << "0: end" << endl;
		cout << "input: ";
		cin >> option;
		system("CLS");
		if (option.length() != 1) {
			cout << "[Error] Wrong input! Please check you input!" << endl;
			continue;
		}
		char opn = option[0];
		if (opn == '1') {
			int gomenu = -1;
			while (1) {
				string input;
				cout << "*Choose Stage*" << endl;
				cout << "1~3: Easy stage" << endl;
				cout << "4~6: Expert stage" << endl;
				cout << "  0: Go back to Main menu" << endl;
				cout << "Select stage: ";
				cin >> input;
				char opt;
				system("CLS");
				if (input.length() != 1) {
					cout << "[Error] Wrong input! Please choose number in 1~6!" << endl;
					continue;
				}
				else {
					opt = input[0];
					if (opt == '0') {
						gomenu = 1;
						break;
					}
					else if ( opt <= '6' && opt >= '1') {
						try {
							int stage_num = opt - '0';
							Game game(stage_num);
							Blocks stage(stage_num); // 블록들을 file에서 읽어온다
							for (size_t i = 0; i < 36; i++)
							{
								Block current = stage.Current();
								Block next = stage.Next();

								game.AddBlock(current);
								game.AddNextBlock(next);

								
								do {
									cout << game << endl;
									cout << "INPUT instructino: ";
									cin >> inst;
									if (inst != 'w' && inst != 'a' && inst != 's' && inst != 'd') {
										cout << "\nPlsease valid instruction" << endl;
										continue;
									}
									game.GetInstruction(inst);

									while (game.Bomb()) {
										Sleep(1000);
										system("CLS");
										cout << game << endl;
										game.Down();
										Sleep(1000);
										system("CLS");
										cout << game << endl;
									}
									
									system("CLS");
								} while (inst != 's');
								cout << game << endl;
												
								/*if (game.Bomb()) {
									Sleep(1000);
									cout << game << endl;
								}
								game.Down();
								*/
							}									
							
						}
						catch (string fname) {
							cout << "[Error] File '" << fname << "' is not in directory!" << endl;
							continue;
						}
					}
					else {
						cout << "[Error] Wrong input! Please choose number in 1~6!" << endl;
						continue;
					}
				}
				gomenu = 0;
				break;
			}
			if (gomenu == 1) { continue; }
		}
		else if (opn == '2') {

		}
		else if (opn == '0') {
			cout << "Bye Bye" << endl;
			return 0;
		}
		else {
			cout << "[Error] Wrong input! Please check you input!" << endl;
			continue;
		}
		break;
	}
	
	
	return 0;

}



