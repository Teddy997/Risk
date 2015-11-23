#pragma once
#include <vector>
#include <fstream>
#include <string>
#include "GameState.h"
#include "InputProcedure.h"
#include "SaveLoadManager.h"

class Engine
{
private:
	GameState gameState; // the state of the game.
	SaveLoadManager saveLoadManager;
	bool victory, defeat; 

	void startPhase();
	void reinforcementPhase();
	void attackPhase();
	void fortificationPhase();
	void generateAIPlayers(); // asks the user for the number of AI players to play against( 1 to 3)

	void chooseMap(); // choose a map from the available maps

	void assignCountries();

	bool victoryConditions(); // checks after each player's turn if anybody won or if the human player lost

	void gamePlayPhase();

	void createSaveFile();
	void chooseGame();
	void saveGame();
	void loadGame(std::string filename);
public:
	Engine();
	~Engine();
	

};

