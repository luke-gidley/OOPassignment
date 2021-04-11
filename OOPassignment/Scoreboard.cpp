#include "Scoreboard.h"

Scoreboard::Scoreboard()
{
	loadScores();
}



Scoreboard::~Scoreboard()
{
	
}




void Scoreboard::loadScores()
{
	ifstream fin(L"scores.txt", ios::in);

	if (!fin.fail())
	{
		string line;
		while (getline(fin, line)) {

			stringstream ss(line);

			SCORE score;
			ss >> score.name >> score.score >> score.time.mins >> score.time.seconds;
			scores.push_back(score);
			
		}
		fin.close();
	}
}



void Scoreboard::displayScoreboard(EasyGraphics* canvas)
{
	const int PADDING = 40;
	int x = 30;
	int y = 30;
	canvas->clearScreen(canvas->BLACK);
	for (int i = 0; i < MAX_STORED_SCORES && i < scores.size(); i++)
	{
		string score = to_string(i+1) + ". " + scores.at(i).name + ": Score: " + to_string(scores.at(i).score) + " Time: " + to_string(scores.at(i).time.mins) + " Mins, " + to_string(scores.at(i).time.seconds) + " Seconds";
		canvas->drawText(score.c_str(), x, y);
		y += PADDING;
	}

	canvas->drawRectangle(500, 50, 250, 100, false);
	canvas->drawText("Click here to restart game!", 505, 55);
}



void Scoreboard::sortScores()
{
	insertionSort(scores, scores.size());
	reverse(scores.begin(), scores.end());
}



void Scoreboard::addScore(SCORE score)
{
	scores.push_back(score);
}

template <typename T>
void Scoreboard::insertionSort(vector<T> &a, int n)
{
	T temp = a[0];
	for (int i = 0; i < n; i++)
	{
		temp = a[i];
		int j = 0;
		for (j = i; j > 0; j--)
			if (temp < a[j - 1])
				a[j] = a[j - 1];
			else break;
		a[j] = temp;
	}
}

void Scoreboard::storeScores()
{
	
	ofstream fout(L"scores.txt", ios::trunc);
	//insertionSort(scores, scores.size());
	if (!fout.fail())
	{
		for (int i = 0; i < MAX_STORED_SCORES && i < scores.size(); i++)
		{
			fout << scores.at(i).name << " " << to_string(scores.at(i).score) << " " << scores.at(i).time.mins << " " << scores.at(i).time.seconds << " " << "\n";
		}
	}
	fout.close();
}