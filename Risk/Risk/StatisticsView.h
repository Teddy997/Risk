#pragma once
#include "GameState.h"
#include <fstream>
class StatisticsView : public Observer
{
public:
	StatisticsView();
	~StatisticsView();
	StatisticsView(GameState* game);
	void Update();
	void display();
	GameState* getGameState();
private:

	GameState* gameState;
};

