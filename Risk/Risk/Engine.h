#pragma once
#include <vector>
#include <fstream>
#include <string>
#include "GameState.h"
#include "InputProcedure.h"
#include "SaveLoadManager.h"
#include "StatisticsWorld.h"
class Engine
{
private:
	GameState* gameState; // the state of the game.
	bool loaded;
	SaveLoadManager saveLoadManager;
	bool victory, defeat; 

	void startPhase();
	void cardCashingPhase();
	void reinforcementPhase();
	void attackPhase();
	void fortificationPhase();
	void generateAIPlayers(); // asks the user for the number of AI players to play against( 1 to 3)

	void chooseMap(); // choose a map from the available maps

	void assignCountries();

	bool victoryConditions(); // checks after each player's turn if anybody won or if the human player lost

	void gamePlayPhase();
	void loadedGamePlayPhase();

	void createSaveFile();
	void chooseGame();
	void saveGame();
	void loadGame(std::string filename);
	void chooseStats();
	void chooseMapObs();
	void choosePlayerObs();
public:
	Engine();
	void startGame();
	~Engine();
	

};

