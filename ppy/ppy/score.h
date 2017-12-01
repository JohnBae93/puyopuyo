//
// Created by hong on 2017-12-01.
//

#ifndef TERM_ALGORITHM_H
#define TERM_ALGORITHM_H

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
	Score(T c, T s, string n);
	virtual void ShowScore();
	T GetScore();
	T GetCombo();
};

template <typename T>
class AvgScore : public Score{
public:
	AvgScore(Score* sco, int n);
	void ShowScore();
};

template <typename T>
class Scores {
	int sconum;
	Score* sco;

public:
	Scores();
	~Scores();
	void AddScore(Score s);
	void ShowScores();
};


#else
#endif //TERM_ALGORITHM_H