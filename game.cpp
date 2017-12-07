#include <iostream>
#include <queue>

#include "game.h"

int mx[4] = {0, -1, 0, 1};
int my[4] = {1, 0, -1, 0};

Game::Game(int _stage) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            map[i][j] = 0;
        }
    }
    stage = _stage;
    combo = 0;
    score = 0;
    block_left = 35;
	max_combo = 0;
}

void Game::AddBlock(Block block) {
    new_block = block;
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

	int front;
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

void Game::Down(int _combo) {
	int count = 0;
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			if (map[j][i] == 5) {
				count++;
				for (int k = j; k >= 0; k--)
				{	
					if (k == 0) 
						map[k][i] = 0;
					else
						map[k][i] = map[k - 1][i];
				}
			}
		}
	}
	score += count * _combo;
	combo = _combo;
	if (combo > max_combo)
		max_combo = combo;
}

int Game::GetInstruction(char instruction) {
	if (!new_block.Action(instruction)) {
		if (this->DownNewBlock() == 0)
			return 0; // fail to down. game over;
		if(block_left)
			new_block = next_block;
		block_left--;
	}	
	return 1;
}

int Game::DownNewBlock() {
	int first_x = new_block.FirstX();
	int first_y = new_block.FirstY();
	int first_color = new_block.FirstColor();
	int second_x = new_block.SecondX();
	int second_y = new_block.SecondY();
	int second_color = new_block.SecondColor();

	if (first_y == second_y) {
		int bottom = first_x > second_x ? 0 : 1; // first bottom: 0, second bottom : 1
		if (map[0][first_y] != 0) {
			return 0;
		}
		for (int i = 1; i <= HEIGHT; i++)
		{
			
			if ((i == HEIGHT || map[i][first_y] != 0) && bottom == 0) { // first block at bottom
				map[i - 1][first_y] = first_color;
				map[i - 2][first_y] = second_color;
				break;
			}
			else if ((i == HEIGHT || map[i][first_y] != 0 ) && bottom == 1) { // second block at bottom
				map[i - 1][first_y] = second_color;
				map[i - 2][first_y] = first_color;
				break;
			}
		}
	}
	else {
		int first = 0, second = 0;
		if (map[0][first_y] != 0) {
			return 0;
		}
		if (map[0][second_y] != 0) {
			return 0;
		}
		for (int i = 0; i <= HEIGHT; i++)
		{
			if (first == 0 && (i == HEIGHT || map[i][first_y] != 0)) {
				map[i - 1][first_y] = first_color;
				first = 1;
			}
			if (second == 0 && (i == HEIGHT || map[i][second_y] != 0)) {
				map[i - 1][second_y] = second_color;
				second = 1;
			}
		}
	}
	return 1;	
}

int Game::GetScore() {
	return score;
}

ostream &operator<<(ostream &os, Game &game) {
    os << " -------------";
    os << " -------STAGE " << game.stage << "------- ";
    os << endl;
	os << "|";
	int first_x = game.new_block.FirstX();
	int first_y = game.new_block.FirstY();
	int first_color = game.new_block.FirstColor();
	int second_x = game.new_block.SecondX();
	int second_y = game.new_block.SecondY();
	int second_color = game.new_block.SecondColor();

	for (int i = 0; i < WIDTH; i++)
	{
		os << " ";
		if (game.block_left == -1) 
			os << " ";
		else if (first_x == 0 && first_y == i)
			os << first_color;
		else if (second_x == 0 && second_y == i)
			os << second_color;
		else
			os << " ";
	}
    os << " |                     |";
    os << endl;
	os << "|";
	for (int i = 0; i < WIDTH; i++)
	{
		os << " ";
		if (game.block_left == -1)
			os << " ";
		else if (first_x == 1 && first_y == i)
			os << first_color;
		else if (second_x == 1 && second_y == i)
			os << second_color;
		else
			os << " ";
	}
    os << " |                     |";
    os << endl;
    for (int i = 0; i < HEIGHT; ++i) {
        os << "| ";
        for (int j = 0; j < WIDTH; ++j) {
            os << game.map[i][j] << " ";
        }
        os << "|";
        switch (i) {
            case 0:
				os << " Max combo : " << game.max_combo;
				for (size_t i = 0; i < 8 - to_string(game.max_combo).length(); i++)
				{
					os << " ";
				}
				os << "|";
                os << endl;
                break;
            case 1:
				os << " score : " << game.score;
				for (size_t i = 0; i < 12 - to_string(game.score).length(); i++)
				{
					os << " ";
				}
				os << "|";
                os << endl;
                break;
            case 2:
				if (game.block_left >= 0) {
					os << " block left : " << game.block_left;
					for (size_t i = 0; i < 7 - to_string(game.block_left).length(); i++)
					{
						os << " ";
					}
					os << "|";
				}
				else {
					os << " block left : 0      |";
				}
                os << endl;
                break;
            case 5:
                os << " next puyo : " << "        |";
                os << endl;
                break;
            case 6:
				if (game.block_left <= 0) {
					os << "     end             |";
				}else {
					os << "         "<< game.next_block.FirstColor() << " " 
					<< game.next_block.SecondColor() << "         |";
				}
                os << endl;
                break;
            case 9:
                os << " instruction :" << "       |";
                os << endl;
                break;
            case 10:
                os << "   a: left, d: right," << "|";
                os << endl;
                break;
            case 11:
                os << "   w: turn, s: down  " << "|";
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
	cout << endl << "-----  stage " << stage << " -----" << endl;
	cout << "[MAX COMBO] " << max_combo << endl;
	cout << "[SCORE] " << score << endl << endl;
	cout << "Enter your name: ";
	string name;
	cin >> name;
	system("CLS");
	if (name.length() > 10) {
		name = name.substr(0, 9);
	}
	Score<int> s;
	s.SetScore(score);
	s.SetName(name);
	s.SetCombo(max_combo);
	try {
		Scores rank(stage);
		rank.AddScore(s, stage);
		cout << "Please enter anything to continue...";
		cin >> name;
		system("CLS");
		return;
	}
	catch (string fname) {
		cout << "[Error] File '" << fname
			<< "' is not in directory!" << endl;
	}

}