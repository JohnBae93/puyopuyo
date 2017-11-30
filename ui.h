//
// Created by John on 2017-11-17.
//

#ifndef TERM_UI_H
#define TERM_UI_H

#include "algorithm.h"
using namespace std;

#define HEIGHT 12
#define WIDTH 6

class Game{
private:
    int stage;
    int map[HEIGHT][WIDTH];  // [12][6]
    int combo;
    int score;
    int block_left;
    Block new_block;
    Block next_block;
public:
    Game(int stage);
    void AddBlock(Block block);
    void AddNextBlock(Block block);
    int Bomb();
    void Down();
    friend ostream &operator<<(ostream &os, Game &map);
    ~Game();
};


#else
#endif //TERM_UI_H
