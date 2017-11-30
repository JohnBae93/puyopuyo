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
	map[10][0] = 1;
	map[9][0] = 1;
	map[8][0] = 1;

}

void Game::AddBlock(Block *block) {
    new_block = block;
	block_left--;
}

void Game::AddNextBlock(Block block) {
    next_block = block;
}

int Game::Bomb() {
    vector<vector<int> > queue;  // x, y, color
    vector<int> tmp;
    tmp.resize(3);
    vector<int> pop;
    pop.resize(3);
    int count;
	int isBomb = 0;
	int newx, newy;

	int front = 0;

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (map[i][j] > 0 && map[i][j] < 5) {
                tmp[0] = i; tmp[1] = j; tmp[2] = map[i][j];
                queue.push_back(tmp);

                map[i][j] = 5;
                count = 1;
				front = 0;
                while (front != queue.size()) {
                    pop = queue[front];
					front++;
                    for (int k = 0; k < 4; ++k) {
						newx = pop[0] + mx[k]; newy = pop[1] + my[k];
						if (newx >= 0 && newx < HEIGHT && newy >= 0 && newy < WIDTH) {
							if (map[newx][newy] == pop[2]) {
								tmp[0] = newx; tmp[1] = newy; tmp[2] = pop[2];
								queue.push_back(tmp);

								map[newx][newy] = 5;
								count++;
							}
						}
                    }
                }
                if(count < 4) {
                    for (int k = 0; k < count ; ++k) {
                        map[queue[k][0]][queue[k][1]] = queue[k][2];
                    }
				}
				else {
					isBomb = 1;
				}
				queue.clear();
            }

        }
    }
	return isBomb;
}

void Game::Down() {
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = HEIGHT - 1; j >= 0; j--)
		{
			if (map[j][i] == 5) {
				for (int k = j; k < HEIGHT; k++)
				{	
					if (i == WIDTH) 
						map[k][i] = 0;
					else
						map[k][i] = map[k + 1][i];
				}
			}
		}
	}
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