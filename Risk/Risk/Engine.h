#pragma once
#include <vector>
#include "Map.h"
#include "GameState.h"


class Engine
{
private:
	GameState gameState;
	bool victory, defeat;
	void startPhase();
	void reinforcementPhase();
	void attackPhase();
	void fortificationPhase();
	void generateAIPlayers();
	void chooseMap();
	void assignCountries();
	bool victoryConditions();

public:
	Engine();
	~Engine();
	void gamePlayPhase();

};

