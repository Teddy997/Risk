#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Map.h"
#include <cereal/archives/xml.hpp>
#include "AgressiveStrategy.h"
#include "DefensiveStrategy.h"
#include "RandomStrategy.h"
using namespace std;


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
	
	void updatePlayerTurn(int turn);
	Player* getMainPlayer();
	Player* getCurrentPlayer();
	vector<Player*> getAIPlayers();
	void setMap(string str);
	void displayMapDirectoryContents();
	void assignCountries();
	
	// This method lets cereal know which data members to serialize
	
	template<class Archive>
	//Keep it inline for now, it causes a linker problem otherwise
	
	void serialize(Archive & archive) { archive(
		
		CEREAL_NVP(currentPlayer),
		CEREAL_NVP(player),
		CEREAL_NVP(AIPlayers),
		CEREAL_NVP(currentPhase),
		CEREAL_NVP(map));
		
	};
	
	void setPlayerTurn(Player* p);
private:
	Player player;
	vector<Player> AIPlayers;
	Map map;
	Phase currentPhase;
	void reinforcingPhase();
	Player currentPlayer;
	void doAIReinforcement(int armies);
};

