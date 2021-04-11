#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include "SharedData.h"

using namespace std;

struct TIME
{
	int mins;
	int seconds;
	bool operator>(const TIME rhs)
	{
		if (this->mins == rhs.mins)
		{
			return (this->seconds > rhs.seconds);
		}
		else
		{
			return (this->mins > rhs.mins);
		}
	}

	bool operator<(const TIME rhs)
	{
		if (this->mins == rhs.mins)
		{
			return (this->seconds < rhs.seconds);
		}
		else
		{
			return (this->mins < rhs.mins);
		}
	}

};

struct SCORE
{
	string name;
	int score;
	TIME time;

	bool operator>(const SCORE rhs) 
	{
		switch (SharedData::getSharedData()->getScoreboardSortType())
		{
		case 1:
			return (this->score > rhs.score);
			break;
		case 2: 
			return (this->time > rhs.time);
			break;
		default:
			break;
		}
		return false;
	}
	bool operator<(const SCORE rhs)
	{
		switch (SharedData::getSharedData()->getScoreboardSortType())
		{
		case 1:
			return (this->score < rhs.score);
			break;
		case 2:
			return (this->time < rhs.time);
			break;
		default:
			break;
		}
		return false;
	}
};



class Scoreboard
{
public:

	Scoreboard();
	~Scoreboard();

	void loadScores();
	void displayScoreboard(EasyGraphics* canvas);
	void sortScores();
	void addScore(SCORE score);
	void storeScores();

	template <typename T>
	void insertionSort(vector<T>& a, int n);

private:

	vector<SCORE> scores;
	const int MAX_STORED_SCORES = 10;


};

