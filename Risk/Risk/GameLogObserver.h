#pragma once
#include "GameState.h"
#include <fstream>

class GameLogObserver : public Observer {
public:
	GameLogObserver();
	~GameLogObserver();
	void update();
	void display();
	GameState* getGameState();
private:
	GameState* game;
};