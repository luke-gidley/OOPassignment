#pragma once
#include <string>

using namespace std;

class Time
{
public:
	Time(string name, int mins, int seconds);
	~Time();
	bool operator>(const Time* rhs);
	bool operator<(const Time* rhs);
	Time& operator=(const Time* rhs);

	string getName();
	int getMins();
	int getSecs();

private:

	int mins, seconds;
	string name;

};
//compares to see if the mins are the same, if they are it compares seconds, if not compares mins.
inline bool Time::operator>(const Time* rhs)
{
	if (this->mins == rhs->mins)
	{
		return (this->seconds > rhs->seconds);
	}
	else
	{
		return (this->mins > rhs->mins);
	}
}

inline bool Time::operator<(const Time* rhs)
{
	if (this->mins == rhs->mins)
	{
		return (this->seconds < rhs->seconds);
	}
	else
	{
		return (this->mins < rhs->mins);
	}
}

inline string Time::getName() { return name; }

inline int Time::getMins() { return mins; }

inline int Time::getSecs() { return seconds; }

inline Time& Time::operator=(const Time* rhs)
{
	this->name = rhs->name;
	this->mins = rhs->mins;
	this->seconds = rhs->seconds;
	return *this;
}

inline Time::Time(string name, int mins, int secs) : name(name), mins(mins), seconds(secs)
{

}

inline Time::~Time()
{

}