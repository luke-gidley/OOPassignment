#include "Level.h"
#include <time.h>
#include <stdlib.h>
#include "SharedData.h"


const int BLOCK_AMOUNT_ROW = 39;
const int BLOCK_AMOUNT_COLUMN = 10;
const int BLOCK_WIDTH = 20;
const int BLOCK_HEIGHT = 12;
const int colours[10] = { EasyGraphics::DARK_RED, EasyGraphics::RED, EasyGraphics::YELLOW, EasyGraphics::GREEN, EasyGraphics::BLUE, EasyGraphics::DARK_GREEN, EasyGraphics::DARK_MAGENTA, EasyGraphics::MAGENTA, EasyGraphics::WHITE, EasyGraphics::CYAN };
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int REDRAW_TIMER_ID = 1;
const int SCOREBOARD_SCORE_SORT = 1;
const int SCOREBOARD_TIME_SORT = 2;


Level::Level() : levelStarted(false), nameEntered(false), scoreboardSelected(false)
{
	setImmediateDrawMode(false);
	blocks = createLevel();
	paddle = createPaddle();
	ball = createBall();
	scoreboard = new Scoreboard();
}

//memory cleanup for anything that hasn't already been deleted during the course of the game.
Level::~Level() 
{
	for (int i = 0; i < blocks->size(); i++)
	{
		delete blocks->at(i);

	}
	delete blocks;
	delete paddle;
	delete ball;
	scoreboard->storeScores();
	delete scoreboard;

}

void Level::onDraw()
{
	clearScreen(BLACK);
	if (!levelStarted) {
		setFont(20, L"Arial");
		drawText(L"Click to start", SCREEN_WIDTH / 2 - 50, 500);
	}

	if (!SharedData::getSharedData()->getGameOver())
	{

		bool spawnPowerUp = false;
		
		//for each loops each drawing a blocks.
		for_each(blocks->begin(), blocks->end(), [this](Block* block) {block->drawBlock(this); });

		//for each loop checking for collision.
		for_each(SharedData::getSharedData()->getPowerUps()->begin(), SharedData::getSharedData()->getPowerUps()->end(), [this](PowerUp* powerUp) {powerUp->collision(paddle); });

		//for each loop drawing powerups
		for_each(SharedData::getSharedData()->getPowerUps()->begin(), SharedData::getSharedData()->getPowerUps()->end(), [this](PowerUp* powerUp) {powerUp->drawPowerUp(this); });

		//collision and drawing for ball and paddle.
		ball->collision(blocks, paddle);
		ball->drawBall(this);
		paddle->drawPaddle(this);

		//drawing powerup key.
		setBackColour(RED);
		setFont(15, L"Arial");
		drawCircle(50, 450, 5, true);
		drawText(" - Bigger Paddle Powerup", 60, 435);
		setBackColour(GREEN);
		drawCircle(50, 480, 5, true);
		drawText(" - Double Speed Powerup", 60, 465);
		setBackColour(BLUE);
		drawCircle(50, 510, 5, true);
		drawText(" - Juggernaut Powerup", 60, 495);
	}

	//if someone breaks every block game ends.
	if (blocks->size() == 0 && !SharedData::getSharedData()->getGameOver())
	{
		SharedData::getSharedData()->changeGameOver();
	}

	//sets up the next screen once the game has ended, things like time taken etc then puts them into the score struct.
	if (SharedData::getSharedData()->getGameOver())
	{
		if (!stopTime) {
			timeTaken = difftime(time(0), start);
			score.score = SharedData::getSharedData()->getScore();
			score.time.mins = calcTime(timeTaken);
			score.time.seconds = timeTaken;
		}
		stopTime = true;
		showGameOver();

		if(scoreboardSelected)
			scoreboard->displayScoreboard(this);
	}
	EasyGraphics::onDraw();
}

//creates the blocks inside the level.
vector<Block*>* Level::createLevel()
{
	int x = 2;
	int y = 0;
	
	vector<Block*>* levelBlocks = new vector<Block*>;

	//for loops creating each collumn and row of blocks.
	for (int i = 0; i < BLOCK_AMOUNT_COLUMN; i++)
	{
		for (int j = 0; j < BLOCK_AMOUNT_ROW; j++)
		{
			bool containsPowerUp = false;
			int chanceToContainPowerUp = rand() % 10 + 1;

			if (chanceToContainPowerUp >= 9)
			{
				containsPowerUp = true;
			}

			Block* block = new Block(x, y, BLOCK_WIDTH, BLOCK_HEIGHT, colours[i], 1, containsPowerUp);
			levelBlocks->push_back(block);
			x += BLOCK_WIDTH;
		}
		y += BLOCK_HEIGHT;
		x = 2;
	}
	return levelBlocks;
}

//moves paddle, with powerups like double time it would be unfair to force it to be key presses as the ball is pretty quick during double time.
void Level::onMouseMove(UINT nFlags, int x, int y)
{
	if (x > 0 + paddle->getWidth()/2 && x < SCREEN_WIDTH - paddle->getWidth() / 2) {
		paddle->movePaddle(x - paddle->getWidth() / 2);
	}
}


Paddle* Level::createPaddle()
{
	Paddle* paddle = new Paddle(400, 400, 50, 20);
	return paddle;
}

Ball* Level::createBall()
{
	Ball* ball = new Ball(400, 375, 10, 45, 5);
	return ball;
}

//starts game, checks for button clicks
void Level::onLButtonDown(UINT nFlags, int x, int y)
{
	if (!levelStarted)
	{
		levelStarted = true;
		
		ball->changeDirection() = ball->startMovement(ball->getAngle());
		setTimer(REDRAW_TIMER_ID, 1);
		start = time(0);
	}
	if (nameEntered && !scoreboardSelected)
	{
		if ((x >= 25 && x <= 225) && (y >= 300 && y <= 360))
		{
			scoreboardSelected = true;
			SharedData::getSharedData()->changeScoreboardType(SCOREBOARD_SCORE_SORT);
			scoreboard->sortScores();
		}
		else if ((x >= 325 && x <= 525) && (y >= 300 && y <= 360))
		{
			scoreboardSelected = true;
			SharedData::getSharedData()->changeScoreboardType(SCOREBOARD_TIME_SORT);
			scoreboard->sortScores();
		}
		onDraw();
	}

	if (scoreboardSelected)
	{
		if ((x >= 500 && x <= 750) && (y >= 50 && y <= 150))
		{
			SharedData::getSharedData()->setGameEnded(false);
			DestroyWindow(EasyGraphics::getHWND());
		}
	}
}

void Level::onTimer(UINT nIDEvent)
{
	if (nIDEvent == REDRAW_TIMER_ID) {
		ball->moveBall();

		for_each(SharedData::getSharedData()->getPowerUps()->begin(), SharedData::getSharedData()->getPowerUps()->end(), [](PowerUp* powerUp) {powerUp->movePowerUp(); });

		if (SharedData::getSharedData()->getBigPaddleActive())
		{
			SharedData::getSharedData()->changeBigPaddleTimer(-1);
			if (SharedData::getSharedData()->getBigPaddleTimer() == 0)
			{
				paddle->changeWidth(-100);
				SharedData::getSharedData()->changeBigPaddleActive();
			}
		}

		if (SharedData::getSharedData()->getJuggernautActive())
		{
			SharedData::getSharedData()->changeJuggernautTimer(-1);
			if (SharedData::getSharedData()->getJuggernautTimer() == 0)
			{
				SharedData::getSharedData()->changeJuggernautActive();
			}
		}

		if (SharedData::getSharedData()->getDoubleSpeedActive())
		{
			SharedData::getSharedData()->changeDoubleSpeedTimer(-1);
			if (SharedData::getSharedData()->getDoubleSpeedTimer() == 0)
			{
				SharedData::getSharedData()->changeDoubleSpeedActive();
			}
		}	
	}
	onDraw();
}


void Level::showGameOver()
{
	killTimer(REDRAW_TIMER_ID);
	clearScreen(BLACK);
	setFont(20, L"Arial");
	string scoreString = "Your scored " + to_string(score.score) + " points!";
	string timeString = "Your time is: " + to_string(score.time.mins) + " mins and " + to_string(score.time.seconds) + " seconds";
	drawText(scoreString.c_str(), 25, 50);
	drawText(timeString.c_str(), 25, 100);
	if (!nameEntered)
	{
		string name = "Write name here: " + score.name;
		drawText(name.c_str(), 25, 150);
	}
	else if (nameEntered)
	{
		drawText("Please select a scoreboard!", 25, 150);

		setPenColour(WHITE, 5);

		drawRectangle(25, 300, 200, 60, false);
		setFont(15, L"Arial");
		drawText("Click here to sort the", 30, 310);
		drawText("scoreboard by score!", 30, 330);

		drawRectangle(325, 300, 200, 60, false);
		drawText("Click here to sort the", 330, 310);
		drawText("scoreboard by time!", 330, 330);
	}
}

int Level::calcTime(int& seconds)
{
	int mins = seconds / 60;
	seconds = seconds % 60;
	return mins;
}

void Level::onKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	char press = nChar;

	if (press >= 'A' && press <= 'Z' && !nameEntered)
	{
		if(score.name.length() < 7)
			score.name += press;
		onDraw();
	}
	if (press == VK_BACK && !nameEntered)
	{
		if (score.name.length() > 0)
			score.name.erase(score.name.size() - 1, 1);
		onDraw();
	}
	if (press == VK_RETURN && SharedData::getSharedData()->getGameOver() && !nameEntered)
	{
		nameEntered = true;
		scoreboard->addScore(score);
	}
	onDraw();
}


void Level::onCreate() {

	EasyGraphics::onCreate();

	SetWindowText(getHWND(), L"Breakout Game");
}

