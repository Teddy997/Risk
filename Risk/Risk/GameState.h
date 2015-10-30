#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Map.h"
#include <cereal/archives/xml.hpp>

using std::vector;
using std::string;



enum Phase {
	GETTING,
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
	void updatePlayerTurn();
	Player getMainPlayer();
	Player* getCurrentPlayer();
	vector<Player> getAIPlayers();
	void setMap(string str);
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
	// TODO: Not sure which data type here yet, I'll find out soon - C
	int currentPlayerTurn;
};

