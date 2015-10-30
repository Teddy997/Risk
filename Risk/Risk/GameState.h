#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Map.h"
#include <cereal/archives/binary.hpp>



class GameState
{
public:
	enum Phase{
		GETTING,
		ATTACKING,
		FORTIFYING
	};
	GameState();
	~GameState();
	void addPlayer(std::string name);
	void changeGamePhase(Phase newPhase);
	void updatePlayerTurn();
	Player* getCurrentPlayer();
	// This method lets cereal know which data members to serialize
	template<class Archive>
	void serialize(Archive & archive) { archive(CEREAL_NVP(currentPlayerTurn)); };

private:
	std::vector<Player> players;
	Map map;
	Phase currentPhase;
	// TODO: Not sure which data type here yet, I'll find out soon - C
	int currentPlayerTurn = 72;
};

