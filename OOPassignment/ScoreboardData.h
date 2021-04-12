#pragma once
#include <string>

using namespace std;

class ScoreboardData
{
public:

	ScoreboardData(string name, int points, int mins, int secs);
	~ScoreboardData();
	bool operator>(const ScoreboardData* rhs);
	bool operator<(const ScoreboardData* rhs);
	ScoreboardData& operator=(const ScoreboardData* rhs);
	int getMins();
	int getSecs();
	int getPoints();
	string getName();
	void setName(string name);

private:
	int mins, secs, points;
	string name;


};
//comparisions for sorting algorithm 
inline bool ScoreboardData::operator>(const ScoreboardData* rhs)
{
	return (this->points > rhs->points);
}
inline bool ScoreboardData::operator<(const ScoreboardData* rhs)
{
	return (this->points < rhs->points);
}

inline int ScoreboardData::getMins() { return mins; }
inline int ScoreboardData::getSecs() { return secs; }
inline int ScoreboardData::getPoints() { return points; }
inline string ScoreboardData::getName() { return name; }

inline void ScoreboardData::setName(string name) { this->name = name; }
//for reassigning information from one object to another.
inline ScoreboardData& ScoreboardData::operator=(const ScoreboardData* rhs)
{
	this->mins = rhs->mins;
	this->name = rhs->name;
	this->points = rhs->points;
	this->secs = rhs->secs;
	return *this;
}

inline ScoreboardData::ScoreboardData(string name, int points, int mins, int secs) : name(name), points(points), mins(mins), secs(secs)
{

}

inline ScoreboardData::~ScoreboardData()
{

}