#pragma once
#include <vector>
#include "GameState.h"
#include "InputProcedure.h"


class Engine
{
private:
	GameState gameState; // the state of the game.
	bool victory, defeat; 

	void startPhase();
	void reinforcementPhase();
	void attackPhase();
	void fortificationPhase();
	void generateAIPlayers(); // asks the user for the number of AI players to play against( 1 to 3)

	void chooseMap(); // choose a map from the available maps

	// assignCountries() takes portions of countries from the map and assigns them to players. For example, countries
	// 0 to 9 will be assigned to player,
	// 10 to 19 to player 2, 20 to 29 to player 3 etc.
	void assignCountries();

	bool victoryConditions(); // checks after each player's turn if anybody won or if the human player lost

	void gamePlayPhase();
public:
	Engine();
	~Engine();
	

};

