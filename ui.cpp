#include <iostream>
#include <queue>

#include "ui.h"

int mx[4] = {0, -1, 0, 1};
int my[4] = {1, 0, -1, 0};

Game::Game() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            map[i][j] = 0;
        }
    }
    stage = 0;
    combo = 0;
    score = 0;
    block_left = 36;
    map[11][0] = 1;
    map[11][1] = 1;
    map[11][2] = 1;
    map[11][3] = 1;
}

void Game::AddBlock(Block *block) {
    new_block = block;
}

void Game::AddNextBlock(Block block) {
    next_block = block;
}

void Game::Bomb() {
    vector<vector<int> > queue;  // x, y, color
    vector<int> tmp;
    tmp.resize(3);
    vector<int> pop;
    pop.resize(3);
    int count;

    vector<vector<int> >::iterator front ;

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (map[i][j] > 0 && map[i][j] < 5) {
                tmp[0] = i; tmp[1] = j; tmp[2] = map[i][j];
                queue.push_back(tmp);

                map[i][j] = 5;
                count = 1;
                front = queue.begin();
                while (!queue.empty()) {
                    pop = *front;

                    for (int k = 0; k < 4; ++k) {
                        if(map[i + mx[k]][j + my[k]] == pop[2]){
                            tmp[0] = i + mx[k]; tmp[1] = j +  my[k]; tmp[2] = pop[2];
                            queue.push_back(tmp);

                            map[i + mx[k]][j + my[k]] = 5;
                            count ++;
                        }
                    }
                    front++;
                }
                if(count < 4) {
                    for (front = queue.begin(); front != queue.end() ; ++front) {
                        map[(*front)[0]][(*front)[1]] = (*front)[2];
                    }
                }
            }

        }
    }
}

void Game::Down() {

}

ostream &operator<<(ostream &os, const Game &game) {
    os << " -------------";
    os << " -------STAGE " << game.stage << "------- ";
    os << endl;
    os << "|             |" << "                     |";
    os << endl;
    os << "|     2 3     |" << "                     |";
    os << endl;
    for (int i = 0; i < HEIGHT; ++i) {
        os << "| ";
        for (int j = 0; j < WIDTH; ++j) {
            os << game.map[i][j] << " ";
        }
        os << "|";
        switch (i) {
            case 0:
                os << " combo : " << game.combo << "           |";
                os << endl;
                break;
            case 1:
                os << " score : " << game.score << "           |";
                os << endl;
                break;
            case 2:
                os << " block left : " << game.block_left << "     |";
                os << endl;
                break;
            case 5:
                os << " next puyo : " << "        |";
                os << endl;
                break;
            case 6:
                os << "      1 2" << "            |";
                os << endl;
                break;
            case 9:
                os << " instruction :" << "       |";
                os << endl;
                break;
            case 10:
                os << "   w: turn, a: left, " << "|";
                os << endl;
                break;
            case 11:
                os << "   d: right, s: down " << "|";
                os << endl;
                break;
            default:
                os << "                     |";
                os << endl;
                break;
        }


    }
    os << " -----------------------------------";

    return os;
}


Game::~Game() {

}