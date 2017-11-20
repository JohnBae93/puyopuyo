//
// Created by John on 2017-11-17.
//

#ifndef TERM_ALGORITHM_H
#define TERM_ALGORITHM_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Block{
	int first_puyo[3]; //y, x, color
	int second_puyo[3]; //y, x, color
	
public:
	Block(int first, int second); //get color of blocks.
	int Action(char command); //get command and move block(1 if rotate, move left, move right && 0 if down)
	void Rotate();
	void MoveLeft();
	void MoveRight();
	int FirstX();
	int FirstY();
	int FirstColor();
	int SecondX();
	int SecondY();
	int SecondColor();
	friend ostream& operator<<(ostream& os, Block& block);;
};

class Blocks {
	int number = 36;
	int puyos[36][2];
	int current;

public:
	Blocks(int stage);
	Block GetBlock(int n); // get (current+n)'th block
	Block Next(); //return current block and current+=1
};


#else
#endif //TERM_ALGORITHM_H
