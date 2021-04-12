#include "Scoreboard.h"

Scoreboard::Scoreboard()
{	
	scoreboardData = new vector<ScoreboardData*>;
	scores = new vector<Score*>;
	times = new vector<Time*>;
	loadScores();
}


//memory cleanup
Scoreboard::~Scoreboard()
{
	for (int i = 0; i < scores->size(); i++)
		delete scores->at(i);
	delete scores;

	for (int i = 0; i < times->size(); i++)
		delete times->at(i);
	delete times;

	for (int i = 0; i < scoreboardData->size(); i++)
		delete scoreboardData->at(i);
	delete scoreboardData;
}



//loads in scores from scores.txt
void Scoreboard::loadScores()
{
	ifstream fin(L"scores.txt", ios::in);

	if (!fin.fail())
	{
		string line;
		while (getline(fin, line)) {

			
			stringstream ss(line);

			int mins, points, secs;
			string name;

			ss >> name >> points >> mins >> secs;

			Score* score = new Score(name, points);
			Time* time = new Time(name, mins, secs);
			ScoreboardData* data = new ScoreboardData(name, points, mins, secs);

			scores->push_back(score);
			times->push_back(time);
			scoreboardData->push_back(data);
		}
		fin.close();
	}
}


//displays scoreboard depending on which one was picked
void Scoreboard::displayScoreboard(EasyGraphics* canvas)
{
	const int PADDING = 40;
	int x = 30;
	int y = 30;
	canvas->clearScreen(canvas->BLACK);

	switch (sortType)
	{
	case 1:
		for (int i = 0; i < MAX_STORED_SCORES && i < scores->size(); i++)
		{
			string score = to_string(i + 1) + ". " + scores->at(i)->getName() + ": Score: " + to_string(scores->at(i)->getScore());
			canvas->drawText(score.c_str(), x, y);
			y += PADDING;
		}
		break;
	case 2:
		for (int i = 0; i < MAX_STORED_SCORES && i < times->size(); i++)
		{
			string score = to_string(i + 1) + ". " + times->at(i)->getName() + ": Time: " + to_string(times->at(i)->getMins()) + " Mins " + to_string(times->at(i)->getSecs()) + " Seconds";
			canvas->drawText(score.c_str(), x, y);
			y += PADDING;
		}
		break;
	}

	canvas->drawRectangle(500, 50, 250, 100, false);
	canvas->drawText("Click here to restart game!", 505, 55);
}


//sorts the scoreboard depending on what type is asked for, expandable of more types needed.
void Scoreboard::sortScoreboard()
{
	switch (sortType)
	{
	case 1:
		insertionSort(scores, scores->size());
		reverse(scores->begin(), scores->end());
		break;
	case 2:
		insertionSort(times, times->size());
		reverse(times->begin(), times->end());
		break;
	}
	
}

//adds the new score to the appropirate vectors.
void Scoreboard::addScoreboardData(ScoreboardData* data)
{
	scoreboardData->push_back(data);
	Score* score = new Score(data->getName(), data->getPoints());
	Time* time = new Time(data->getName(), data->getMins(), data->getSecs());
	scores->push_back(score);
	times->push_back(time);

}

//sorting template for a vector of objects.
template <typename T>
void Scoreboard::insertionSort(vector<T*>* &toSort, int size)
{
	T* temp = toSort->at(0);
	for (int i = 0; i < toSort->size(); i++)
	{
		*temp = *toSort->at(i);
		int j = 0;
		for (j = i; j > 0; j--)
			if (*temp < toSort->at(j - 1))
				*toSort->at(j) = *toSort->at(j - 1);
			else break;
		*toSort->at(j) = *temp;
	}
}

//puts the scores back into the scores.txt, clears it first.
void Scoreboard::storeScores()
{
	
	ofstream fout(L"scores.txt", ios::trunc);
	insertionSort(scoreboardData, scoreboardData->size());
	if (!fout.fail())
	{
		for (int i = 0; i < MAX_STORED_SCORES && i < scoreboardData->size(); i++)
		{
			fout << scoreboardData->at(i)->getName() << " " << to_string(scoreboardData->at(i)->getPoints()) << " " << scoreboardData->at(i)->getMins() << " " << scoreboardData->at(i)->getSecs() << " " << "\n";
		}
	}
	fout.close();
}

