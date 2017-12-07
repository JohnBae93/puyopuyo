//
// Created by hong on 2017-12-01.
//

#include "score.h"
#include <sstream>

template <typename T>
Score<T>::Score() {
	combo = 0;
	score = 0;
}

template <typename T>
Score<T>::Score(T c, T s, string n) {
	combo = c;
	score = s;
	name = n;
}

template <typename T>
void Score<T>::ShowScore() {
	int score_len = to_string(score).length();
	int name_len = name.length();
	cout << name;
	for (size_t i = 0; i < 15 - name_len; i++)
	{
		cout << " ";
	}
	cout << to_string(score);
	for (size_t i = 0; i < 17 - score_len; i++)
	{
		cout << " ";
	}
	cout << to_string(combo);
	cout << endl;
	return;
}

template <typename T>
T Score<T>::GetScore() {
	return score;
}

template <typename T>
T Score<T>::GetCombo() {
	return combo;
}

template <typename T>
void Score<T>::SetScore(T sco) {
	score = sco;
}

template <typename T>
void Score<T>::SetCombo(T com) {
	combo = com;
}

template <typename T>
void Score<T>::SetName(string n) {
	name = n;
}

AvgScore::AvgScore(Score<int>* sco, int n){
	combo = 0.0;
	score = 0.0;
	for (int i = 0; i < n; i++) {
		score += sco[i].GetScore();
		combo += sco[i].GetCombo();
	}
	combo = combo / n;
	score = score / n;
}

void AvgScore::ShowScore() {
	int score_len = to_string(score).length();
	int combo_len = to_string(combo).length();
	cout << "Averge :             ";
	cout << to_string(score);
	for (size_t i = 0; i < 17 - score_len; i++)
	{
		cout << " ";
	} 
	cout << to_string(combo);
	cout << endl;
	return;
}

Scores::Scores(int stage) {
	ifstream inFile;
	string filename = "ScoreBoard" + to_string(stage) + ".txt";
	inFile.open(filename);
	if (!inFile.is_open()) {
		throw filename;
	}
	string temp;
	string name;
	int score, combo, number;
	stringstream ss;
	getline(inFile, temp);
	ss.str(temp);
	ss >> number;
	sconum = number;
	sco = new Score<int>[sconum];
	for (int i = 0; i < sconum; i++) {
		ss.clear();
		getline(inFile, temp);
		ss.str(temp);
		ss >> name >> score >> combo;
		sco[i].SetName(name);
		sco[i].SetScore(score);
		sco[i].SetCombo(combo);
	}

}

Scores::~Scores() {
	delete []sco;
}

void Scores::AddScore(Score<int> s, int stage) {
	if (sconum == 10) {
		if (sco[9].GetScore() > s.GetScore()) {
			cout << "순위에 들지 못했습니다. 다음 기회에..." << endl;
			return;
		}
	}
	else {
		sconum += 1;
		Score<int>* newsco = new Score<int>[sconum];
		memcpy(newsco, sco, (sconum - 1) * sizeof(Score<int>));
		delete[]sco;
		sco = newsco;
	}
	for (int i = sconum - 1; i >0; i--) {
		if (sco[i-1].GetScore() > s.GetScore()) {
			sco[i] = s;
			break;
		}
		else {
			sco[i] = sco[i - 1];
		}
	}



	return;
}

void Scores::ShowScores() {
	AvgScore Avg(sco, sconum);
	cout << "      name           score            combo" << endl;
	for (int i = 1; i <= sconum; i++) {
		cout << i << ".    ";
		sco[i - 1].ShowScore();
	}
	Avg.ShowScore();
	return;
}