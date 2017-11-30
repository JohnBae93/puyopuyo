//
// Created by John on 2017-11-17.
//

#include "algorithm.h"

Block::Block() {
	first_puyo[0] = 2;
	first_puyo[1] = 0;
	first_puyo[2] = 0;
	second_puyo[0] = 3;
	second_puyo[1] = 0;
	second_puyo[2] = 0;
}

Block::Block(int first, int second) {
	first_puyo[0] = 2;
	first_puyo[1] = 0;
	first_puyo[2] = first;
	second_puyo[0] = 3;
	second_puyo[1] = 0;
	second_puyo[2] = second;
}

int Block::Action(char command) {
	if (command == 's') {
		return 0;
	}
	if (command == 'w') {
		Rotate();
	}
	if (command == 'a') {
		MoveLeft();
	}
	if (command == 'd') {
		MoveRight();
	}
	return 1;
}

void Block::Rotate() {
	if (first_puyo[1] == 1) {
		first_puyo[0] += 1;
		first_puyo[1] -= 1;
		return;
	}
	if (second_puyo[1] == 1) {
		second_puyo[0] += 1;
		second_puyo[1] -= 1;
		return;
	}
	if (first_puyo[0] < second_puyo[0]) {
		first_puyo[1] += 1;
		second_puyo[0] -= 1;
		return;
	}
	if (first_puyo[0] > second_puyo[0]) {
		second_puyo[1] += 1;
		first_puyo[0] -= 1;
		return;
	}
}
void Block::MoveLeft() {
	if (first_puyo[0] > 0 && second_puyo[0] > 0) {
		first_puyo[0] -= 1;
		second_puyo[0] -= 1;
	}
}
void Block::MoveRight() {
	if (first_puyo[0] <5 && second_puyo[0] <5) {
		first_puyo[0] += 1;
		second_puyo[0] += 1;
	}
}
int Block::FirstX() { return first_puyo[1]; }
int Block::FirstY() { return first_puyo[0]; }
int Block::FirstColor() { return first_puyo[2]; }
int Block::SecondX() { return second_puyo[1]; }
int Block::SecondY() { return second_puyo[0]; }
int Block::SecondColor() { return second_puyo[2]; }

ostream& operator<<(ostream& os, Block& block) {
	os << to_string(block.FirstColor()) + " " + to_string(block.SecondColor());
	return os;
}


Blocks::Blocks(int stage) {
	string fname = "stage" + to_string(stage) + ".txt";
	ifstream inFile;
	inFile.open(fname);
	if (!inFile.is_open()) {
		cout << fname << " not in directory" << endl;
		throw -1;
	}
	int i = 0;
	string temp;
	while (!inFile.eof()) {
		getline(inFile, temp);
		puyos[i][0] = temp[0] - '0';
		puyos[i++][1] = temp[2] - '0';
	}
	current = 0;
}

Block Blocks::GetBlock(int n) {
	Block block(puyos[current + n][0], puyos[current + n][1]);
	return block;
}
Block Blocks::Next() {
	Block block(puyos[current][0], puyos[current][1]);
	current += 1;
	return block;
}