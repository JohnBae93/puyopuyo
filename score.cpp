//
// Created by hong on 2017-12-01.
//

#include "score.h"


template <typename T>
Score<T>::Score() {
	combo = 0;
	score = 0;
	name = "none";
}

template <typename T>
Score<T>::Score(T c, T s, string n) {
	combo = c;
	score = s;
	name = n;
}

template <typename T>
Score<T>::Score(const Score<T> &A) {
	combo = A.GetCombo();
	score = A.GetScore();
	name = A.GetName();
}

template <typename T>
void Score<T>::ShowScore() {
	int score_len = to_string(score).length();
	int name_len = name.length();
	cout << name;
	for (int i = 0; i < 15 - name_len; i++)
	{
		cout << " ";
	}
	cout << to_string(score);
	for (int i = 0; i < 17 - score_len; i++)
	{
		cout << " ";
	}
	cout << to_string(combo);
	return;
}

template <typename T>
T Score<T>::GetScore() const {
	return score;
}

template <typename T>
T Score<T>::GetCombo() const {
	return combo;
}

template <typename T>
string Score<T>::GetName() const {
	return name;
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

template <typename T>
void Score<T>::Set(Score<T> A) {
	name = A.GetName();
	combo = A.GetCombo();
	score = A.GetScore();
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
	for (int i = 0; i < 17 - score_len; i++)
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
	inFile.close();
}

Scores::~Scores() {
	delete []sco;
}

void Scores::AddScore(Score<int> s, int stage) {
	if (sconum == 10) {
		if (sco[9].GetScore() > s.GetScore()) {
			ShowScores();
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
			sco[i].Set(s);
			break;
		}
		else {
			sco[i].Set(sco[i - 1]);
		}

		if (i == 1) {
			sco[0].Set(s);
		}
	}
	ShowScores();
	ofstream outFile;
	string filename = "ScoreBoard" + to_string(stage) + ".txt";
	outFile.open(filename);
	if (!outFile.is_open()) {
		throw filename;
	}
	outFile << sconum << endl;
	for (int i = 0; i < sconum; i++) {
		outFile << sco[i].GetName() << " " << sco[i].GetScore() << " " << sco[i].GetCombo() << endl;
	}
	outFile.close();
	return;
}

void Scores::ShowScores() {
	AvgScore Avg(sco, sconum);
	cout << "-----------------Rank Scores--------------------" << endl;
	cout << "                                              " << endl;
	cout << "       name           score            combo  " << endl;
	for (int i = 1; i <= sconum; i++) {
		cout << " ";
		cout << i << ".    ";
		sco[i - 1].ShowScore();
		cout <<endl;
	}
	Avg.ShowScore();
	cout << endl;
	return;
}