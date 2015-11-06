#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Map.h"
#include <cereal/archives/xml.hpp>
#include "AgressiveStrategy.h"
#include "DefensiveStrategy.h"
#include "RandomStrategy.h"
using std::vector;
using std::string;



enum Phase {
	//Changed GETTING to REINFORCING - Eric
	REINFORCING, 
	ATTACKING,
	FORTIFYING
};
class GameState
{
public:

	GameState();
	GameState(std::string name);
	~GameState();
	void addPlayer(std::string name);
	void changeGamePhase(Phase newPhase);
	void reinforcingPhase(Player &currentPlayer); //TODO: remove this and put in private when we implement changeGamePhase
	void updatePlayerTurn();
	Player getMainPlayer();
	Player* getCurrentPlayer();
	vector<Player> getAIPlayers();
	void setMap(string str);
	void displayMapDirectoryContents();
	void generateCountries();
	// This method lets cereal know which data members to serialize
	template<class Archive>
	//Keep it inline for now, it causes a linker problem otherwise
	void serialize(Archive & archive) { archive(
		CEREAL_NVP(currentPlayerTurn),
		CEREAL_NVP(player),
		CEREAL_NVP(AIPlayers),
		CEREAL_NVP(currentPhase),
		CEREAL_NVP(map));
	};


private:
	Player player;
	vector<Player> AIPlayers;
	Map map;
	Phase currentPhase;
	//This is probably better off private and have it called by changeGamePhase.
	//I've made it public for the time being to do testing - Eric
	//void reinforcingPhase(Player &currentPlayer);
	// TODO: Not sure which data type here yet, I'll find out soon - C
	int currentPlayerTurn;
};

