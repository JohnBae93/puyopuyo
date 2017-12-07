//
// Created by hong on 2017-12-01.
//

#ifndef TERM_SCORE_H
#define TERM_SCORE_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


template <typename T>
class Score {
protected:
	string name;
	T score;
	T combo;

public:
	Score();
	Score(T c, T s, string n);
	virtual void ShowScore();
	T GetScore();
	T GetCombo();
	void SetScore(T sco);
	void SetCombo(T com);
	void SetName(string n);
};

class AvgScore : public Score<double>{
public:
	AvgScore(Score<int>* sco, int n);
	void ShowScore();
};


class Scores {
	int sconum;
	Score<int>* sco;
public:
	Scores(int k);
	~Scores();
	void AddScore(Score<int> s, stage);
	void ShowScores();
};


#else
#endif //TERM_ALGORITHM_H