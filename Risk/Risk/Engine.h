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
	// takes portions of countries and assigns them to players. For example, countries (from the 
	// vector of countries inside map) 0 to 9 will be assigned to player,
	// 10 to 19 to player 2, 20 to 29 to player 3 etc.
	void assignCountries();
	bool victoryConditions();

public:
	Engine();
	~Engine();
	void gamePlayPhase();

};

