//
// Created by hong on 2017-12-01.
//

#include "score.h"

template <typename T>
Score::Score(T c, T s, string n) {
	combo = c;
	score = s;
	name = n;
}

template <typename T>
void Score::ShowScore() {
	cout << name << ": " << score << "           " << combo << endl;
	return;
}

template <typename T>
T Score::GetScore() {
	return score;
}

template <typename T>
T Score::GetCombo() {
	return combo;
}

template <typename T>
AvgScore::AvgScore(Score* sco, int n): Score(score, combo) {
	combo = 0;
	score = 0;
	for (int i = 0; i < n; i++) {
		combo += sco[i].GetScore();
		score += sco[i].GetCombo();
	}
	combo = combo / n;
	score = score / n;
}

template <typename T>
void AvgScore::ShowScore() {
	cout << "Averge : " << score << "           " << combo << endl;
}

template <typename T>
Scores::Scores() {
	ifstram inFile;
	inFile.open("ScoreBoard.txt");
	if (!inFile.is_open()) {
		throw 100;
	}
	string temp;
	string temp2;
	int k, i;
	getline(inFile, temp);
	sconum = temp[0];
	sco = new Score[sconum];
	for (int i = 0; i < sconum; i++) {
		getline(inFile, temp);
		k = 0;
		while (temp[k] != ' ') {
			temp2[k] = temp[k];
			k += 1;
		}
		sco[i].name = temp2;
		k += 1;
		i = 0;
		while (temp[k] != ' ') {
			temp2[i] = temp[k];
			i += 1;
			k += 1;
		}
		sco[i].score = atoi(temp2);
		k += 1;
		i = 0;
		while (temp[k]) {
			temp2[i] = temp[k];
			i += 1;
			k += 1;
		}
		sco[i].combo = atoi(temp2);
	}

}

template <typename T>
Scores::~Scores() {
	delete sco;
}

template <typename T>
void Scores::AddScore(Score s) {
	sconum += 1;
	Score* newsco = new Score[sconum];
	memcpy(newsco, sco, (sconum - 1) * sizeof(Score));
	delete[]sco;
	sco = newsco;
	sco[sconum - 1] = s;
	return;
}

template <typename T>
void Scores::ShowScores() {
	AvgScore Avg(sco, sconum);
	for (int i = 1; i <= sconum; i++) {
		cout << i << ": ";
		sco[i - 1].ShowScore();
	}
	Avg.ShowScore();
	return;
}