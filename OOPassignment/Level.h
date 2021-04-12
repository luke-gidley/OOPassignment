#pragma once
#include "EasyGraphics.h"
#include "Block.h"
#include "Paddle.h"
#include "Ball.h"
#include "Scoreboard.h"
#include "ScoreboardData.h"

class Level : public EasyGraphics
{

public:
	Level();
	~Level();

	virtual void onDraw();
	vector<Block*>* createLevel();
	Paddle* createPaddle();
	virtual void onMouseMove(UINT nFlags, int x, int y);
	Ball* createBall();
	virtual void onLButtonDown(UINT nFlags, int x, int y);
	virtual void onTimer(UINT nIDEvent);
	void showGameOver();
	int calcTime(int& seconds);
	virtual void onKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);  
	virtual void onCreate();                                       


private:
	vector<Block*>* blocks;
	Paddle* paddle;
	Ball* ball;
	bool levelStarted;
	time_t start;
	bool stopTime;
	int timeTaken;
	ScoreboardData* score;
	Scoreboard* scoreboard;
	bool nameEntered;
	bool scoreboardSelected;
	string name;
};

