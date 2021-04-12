#pragma once
#include <string>
#include "Time.h"

using namespace std;

class Score
{
public:

	Score(string name, int points);
	~Score();
	bool operator<(const Score* rhs);
	bool operator>(const Score* rhs);
	Score& operator=(const Score* rhs);
	void setScore(int score);
	int getScore();
	string getName();

private:

	int points;
	string name;

};
//comparisions for sorting algorithm.
inline bool Score::operator<(const Score* rhs)
{
	return (this->points < rhs->points);
}

inline bool Score::operator>(const Score* rhs)
{
	return (this->points > rhs->points);
}

inline void Score::setScore(int score)
{
	points = score;
}

inline int Score::getScore() { return points; }

inline string Score::getName() { return name; }

inline Score& Score::operator=(const Score* rhs)
{
	this->points = rhs->points;
	this->name = rhs->name;
	return *this;
}

inline Score::Score(string name, int points) : points(points), name(name)
{

}

inline Score::~Score()
{

}