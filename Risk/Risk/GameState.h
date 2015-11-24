#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Map.h"
#include <cereal/archives/xml.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>
#include "AgressiveStrategy.h"
#include "DefensiveStrategy.h"
#include "RandomStrategy.h"
#include "InputProcedure.h"
#include "MapCreator.h"
using namespace std;

//Smart pointer types
typedef shared_ptr<Player> PPointer;
typedef shared_ptr<Map> MPointer;

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
	
	void removePlayerAtIndex(int i);

	void updatePlayerTurn(int turn); // changes the current player to the player after it

	Player* getMainPlayer(); // returns the human player

	Player* getCurrentPlayer(); // returns the current player

	vector<Player*> getAIPlayers(); // returns the AI players

	void setMap(string str); // initializes the map

	void displayMapDirectoryContents();

	// assignCountries() assigns countries randomly to the player.
	void assignCountries();
	
	// This method lets cereal know which data members to serialize	
	
	template<class Archive>
	//Keep it inline for now, it causes a linker problem otherwise
	
	void serialize(Archive & archive) { 
		PPointer curPl; PPointer pl;
		//The case where currentPlayer is the human player, special precautions must be made
		//Both pointers share ownership over the memory chunk, thus when we call
		//pl = curPl, we increment the internal counter to prevent double deletion, which results in a crash
		if (currentPlayer == player) {
			curPl = make_shared<Player>(*currentPlayer);
			pl = curPl;
		}
		else {
			curPl = make_shared<Player>(*currentPlayer);
			pl = make_shared<Player>(*player);
		}
		vector<PPointer> aiPls;
		for (int i = 0; i < AIPlayers.size(); i++) {
			aiPls.push_back(make_shared<Player>(*AIPlayers.at(i)));
		}

		MPointer mP = make_shared<Map>(*map);
		archive(
			CEREAL_NVP(curPl),
			CEREAL_NVP(pl),
			CEREAL_NVP(aiPls),
			CEREAL_NVP(currentPhase),
			CEREAL_NVP(mP));
	}
	
private:
	Player* player;
	vector<Player*> AIPlayers;
	Map* map;
	Phase currentPhase;
	void reinforcingPhase();
	void fortifyingPhase();
	void attackingPhase();
	
	void updateView();
	int getIndexOfCountry();
	int getArmies(int max);
	Player* currentPlayer;
	void doAIReinforcement(int armies);
	void doAIFortification();
	void doAIAttacking();
	void doPlayerAttacking();
	void doPlayerFortification();
	void displayAttackOptions();
	void setPlayerTurn(Player* p);
	void manageMap();
};

