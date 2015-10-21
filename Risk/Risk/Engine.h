#include <vector>
#include "Map.h"
#pragma once
#include "GameState.h"

using namespace std;
class Engine
{
private:
	GameState gameState;
	vector<Player> AIplayers;
	Player player;
	vector<Country> countries;
	Map map;
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

