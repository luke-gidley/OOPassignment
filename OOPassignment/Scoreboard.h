#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include "SharedData.h"
#include "Score.h"
#include "Time.h"
#include "ScoreboardData.h"

using namespace std;



class Scoreboard
{
public:

	Scoreboard();
	~Scoreboard();

	void loadScores();
	void displayScoreboard(EasyGraphics* canvas);
	void sortScoreboard();
	void storeScores();
	void addScoreboardData(ScoreboardData* data);
	void setSortType(int type);

	//template insertion sort to allow for multiple types of object sorting.
	template <typename T>
	void insertionSort(vector<T*>* &toSort, int n);

private:

	vector<Score*>* scores;
	vector<Time*>* times;
	vector<ScoreboardData*>* scoreboardData;
	const int MAX_STORED_SCORES = 10;
	int sortType;


};

inline void Scoreboard::setSortType(int type)
{
	sortType = type;
}