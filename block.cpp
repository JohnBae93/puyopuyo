//
// Created by John on 2017-11-17.
//

#include "block.h"

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
Block::Block(const Block &A) {
	first_puyo[0] = A.FirstY();
	first_puyo[1] = A.FirstX();
	first_puyo[2] = A.FirstColor();
	second_puyo[0] = A.SecondY();
	second_puyo[1] = A.SecondX();
	second_puyo[2] = A.SecondColor();
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
	if (first_puyo[1] == 0 && second_puyo[1] == 0) {
		second_puyo[1] += 1;
		first_puyo[0] += 1;
		return;
	}
	if (first_puyo[1] == 0 && second_puyo[1] == 1) {
		second_puyo[0] -= 1;
		first_puyo[1] += 1;
		if (second_puyo[0] < 0) {
			second_puyo[0] += 1;
			first_puyo[0] += 1;
		}
		return;
	}
	if (first_puyo[1] == 1 && second_puyo[1] == 1) {
		second_puyo[1] -= 1;
		first_puyo[0] -= 1;
		return;
	}
	if (first_puyo[1] == 1 && second_puyo[1] == 0) {
		second_puyo[0] += 1;
		first_puyo[1] -= 1;
		if (second_puyo[0] > 5) {
			second_puyo[0] -= 1;
			first_puyo[0] -= 1;
		}
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

int Block::FirstX() const { return first_puyo[1]; }
int Block::FirstY() const { return first_puyo[0]; }
int Block::FirstColor() const { return first_puyo[2]; }
int Block::SecondX() const { return second_puyo[1]; }
int Block::SecondY() const { return second_puyo[0]; }
int Block::SecondColor() const { return second_puyo[2]; }
//const 예시 -> 복사 생성자 사용하기 위해서
void Block::SetBlock(int first, int second) {
	first_puyo[0] = 2;
	first_puyo[1] = 0;
	first_puyo[2] = first;
	second_puyo[0] = 3;
	second_puyo[1] = 0;
	second_puyo[2] = second;
}

void Block::SetBlock(Block A) {
	*this = A;
}

Block Block::GetThis() {
	return *this;
}

ostream& operator<<(ostream& os, Block& block) {
	os << to_string(block.FirstColor()) + " " + to_string(block.SecondColor());
	return os;
}


Blocks::Blocks(int stage) {
	ifstream inFile;
	string fname = "stage" + to_string(stage) + ".txt";
	inFile.open(fname);
	if (!inFile.is_open()) {
		throw fname;
	}
	int i = 0;
	string temp;
	while (getline(inFile, temp)) {
		puyos[i][0] = temp[0] - '0';
		puyos[i++][1] = temp[2] - '0';
	}
	current = 0;
	cur = new Block(puyos[current][0], puyos[current][1]);
	nex = new Block(puyos[current + 1][0], puyos[current + 1][1]);
}

Blocks::~Blocks() {
	delete cur;
	delete nex;
}

Block Blocks::Current() {
	return *cur;
}

Block Blocks::Next() {
	current += 1;
	cur->SetBlock(*nex);
	nex->SetBlock(puyos[current + 1][0], puyos[current + 1][1]);
	//오버로딩 예시
	return *cur;
}