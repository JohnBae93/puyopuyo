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
	Block();
	Block(int first, int second); //get color of blocks.
	Block(const Block &A);
	int Action(char command); //get command and move block(1 if rotate, move left, move right && 0 if down)
	void Rotate();
	void MoveLeft();
	void MoveRight();
	int FirstX() const;
	int FirstY() const;
	int FirstColor() const;
	int SecondX() const;
	int SecondY() const;
	int SecondColor() const;
	void SetBlock(int first, int second);
	void SetBlock(Block A);
	Block GetThis();
};

class Blocks {
	int puyos[50][2];
	int current;
	Block *cur;
	Block *nex;

public:
	Blocks(int stage);
	~Blocks();
	Block Current(); // get (current+n)'th block
	Block Next(); //return current block and current+=1
};


#else
#endif //TERM_ALGORITHM_H
