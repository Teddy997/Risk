#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Map.h"
#include <cereal/archives/xml.hpp>
#include "AgressiveStrategy.h"
#include "DefensiveStrategy.h"
#include "RandomStrategy.h"
#include "InputProcedure.h"
#include "MapCreator.h"
using namespace std;


enum Phase { // Keeps track of the phase we are currently in.

	REINFORCING, 
	ATTACKING,
	FORTIFYING
};
class GameState
{
public:

	GameState();
	GameState(std::string name); // initializes the player with a name
	~GameState();
	// adds a player to the game and sets its strategy randomly between aggressive, defensive and random
	void addPlayer(std::string name); 
	void changeGamePhase(Phase newPhase);
	
	void updatePlayerTurn(int turn); // changes the current player to the player after it

	Player* getMainPlayer(); // returns the human player

	Player* getCurrentPlayer(); // returns the current player

	vector<Player*> getAIPlayers(); // returns the AI players

	void setMap(string str); // initializes the map

	void displayMapDirectoryContents();

	// assignCountries() takes portions of countries from the map and assigns them to players. For example, countries
	// 0 to 9 will be assigned to player,
	// 10 to 19 to player 2, 20 to 29 to player 3 etc.
	void assignCountries();
	
	// This method lets cereal know which data members to serialize	
	
	template<class Archive>
	//Keep it inline for now, it causes a linker problem otherwise
	
	void serialize(Archive & archive) { archive(
		
		CEREAL_NVP(*currentPlayer),
		CEREAL_NVP(*player),
		CEREAL_NVP(replaceThisWithAIPlayers),
		CEREAL_NVP(currentPhase),
		CEREAL_NVP(*map));
		
	};
	
	
private:
	Player* player;
	vector<Player> replaceThisWithAIPlayers; // TODO delete this once cereal works with 'AIPlayers'
	vector<Player*> AIPlayers;
	Map* map;
	Phase currentPhase;
	void reinforcingPhase();
	void fortifyingPhase();
	void updateView();
	int getIndexOfCountry();
	int getArmies(int max);
	Player* currentPlayer;
	void doAIReinforcement(int armies);
	void doAIFortification();
	void setPlayerTurn(Player* p);
	void manageMap();
};

