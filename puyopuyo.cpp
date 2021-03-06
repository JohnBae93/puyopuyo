//
// Created by John on 2017-11-17.
//

#include <iostream>
#include <windows.h>

#include "block.h"
#include "game.h"
#include "score.h"

using namespace std;

int main() {
	char inst;
	while (1) {
		string option;
		cout << "-----------PuyoPuyo Remaster------------" << endl;
		cout << "|                                      |" << endl;
		cout << "| made by. jhong, john                 |" << endl;
		cout << "|                                      |" << endl;
		cout << "|                                      |" << endl;
		cout << "| *Main Menu*                          |" << endl;
		cout << "|                                      |" << endl;
		cout << "| 1: Start game                        |" << endl;
		cout << "| 2: View rank                         |" << endl;
		cout << "| 0: End                               |" << endl;
		cout << "|                                      |" << endl;
		cout << "----------------------------------------" << endl << endl;
		cout << "input:";
		cin >> option;
		system("CLS");
		if (option.length() != 1) {
			cout << "[Error] Wrong input! Please check you input!" << endl;
			continue;
		}
		char opn = option[0];
		int gomenu = 0;
		if (opn == '1') {
			while (1) {
				string input;
				cout << "-----------PuyoPuyo Remaster------------" << endl;
				cout << "|                                      |" << endl;
				cout << "| made by. jhong, john                 |" << endl;
				cout << "|                                      |" << endl;
				cout << "|                                      |" << endl;
				cout << "| *Choose Stage*                       |" << endl;
				cout << "|                                      |" << endl;
				cout << "| 1~3: Easy stage                      |" << endl;
				cout << "| 4~6: Expert stage                    |" << endl;
				cout << "| 0  : Go back to Main menu            |" << endl;
				cout << "|                                      |" << endl;
				cout << "----------------------------------------" << endl << endl;
				cout << "input: ";
				cin >> input;
				char opt;
				system("CLS");
				if (input.length() != 1) {
					cout << "[Error] Wrong input! Please choose number in 0~6!" << endl;
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
							Blocks blocks(stage_num); // 블록들을 file에서 읽어온다
							Game game(stage_num);
							Block current;
							Block next;
							for (size_t i = 0; i < 36; i++)
							{
								current = blocks.Current();
								if(i != 35)
									next = blocks.Next();

								game.AddBlock(current);
								game.AddNextBlock(next);
								int over = 0;
								do {
									system("CLS");
									cout << game << endl;
									cout << "INPUT instruction: ";
									cin >> inst;
									if (inst != 'w' && inst != 'a' && inst != 's' && inst != 'd') 
										continue;
									
									if (game.GetInstruction(inst) == 0) {
										cout << "[GAME OVER]" << endl;
										over = 1;
										break;
									}
									system("CLS");
									cout << game << endl;
								} while (inst != 's');
								if (over == 1) {
									break;
								}
								// combo bomb
								int combo = 1;
								while (game.Bomb()) {
									Sleep(1000);
									system("CLS");
									cout << game << endl;
									game.Down(combo++);
									Sleep(1000);
									system("CLS");
									cout << game << endl;
								}
							}
							continue;	
						}
						catch (string fname) {
							cout << "[Error] File '" << fname 
								<< "' is not in directory!" << endl;
							continue;
						}
					}
					else {
						cout << "[Error] Wrong input! Please choose number in 1~6!" << endl;
						continue;
					}
				}
				break;
			}
		}
		else if (opn == '2') {
			while (1) {
				string input;
				cout << "-----------PuyoPuyo Remaster------------" << endl;
				cout << "|                                      |" << endl;
				cout << "| made by. jhong, john                 |" << endl;
				cout << "|                                      |" << endl;
				cout << "|                                      |" << endl;
				cout << "| *View Rank*                          |" << endl;
				cout << "|                                      |" << endl;
				cout << "| 1~6: See rank of stage               |" << endl;
				cout << "| 0  : Go back to Main menu            |" << endl;
				cout << "|                                      |" << endl;
				cout << "|                                      |" << endl;
				cout << "----------------------------------------" << endl << endl;
				cout << "input: ";
				cin >> input;
				char opt;
				system("CLS");
				if (input.length() != 1) {
					cout << "[Error] Wrong input! Please choose number in 0~6!" << endl;
					continue;
				}
				else {
					opt = input[0];
					if (opt == '0') {
						gomenu = 1;
						break;
					}
					else if (opt < '7' && opt >'0') {
						try {
							Scores k(opt-'0');
							k.ShowScores();
							cout << "Please enter anything to continue...";
							cin >> input;
							system("CLS");
							continue;
						}
						catch (string str) {
							cout << "[Error] File '" << str << "' is not in directory" << endl;
						}
					}
					else {
						cout << "[Error] Wrong input! Please choose number in 0~6!" << endl;
						continue;
					}
				}
			}
		}
		else if (opn == '0') {
			cout << "-----------PuyoPuyo Remaster------------" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|         made by. jhong, john         |" << endl;
			cout << "|                                      |" << endl;
			cout << "|             Game Ended               |" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "----------------------------------------" << endl << endl;
			return 0;
		}
		else {
			cout << "[Error] Wrong input! Please check you input!" << endl;
			continue;
		}

		if (gomenu == 1) { continue; }
		break;
	}
	return 0;
}



