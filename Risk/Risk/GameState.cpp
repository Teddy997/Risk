#pragma once
#include "stdafx.h"
#include "GameState.h"

GameState::GameState() {

}
GameState::GameState(std::string name)
{
	player = Player(name);
}


GameState::~GameState()
{
}

void GameState::addPlayer(std::string name) {
	Player p = Player(name);
	int random = rand() % 3;
	if (random == 0)
		p.setStrategy(new AgressiveStrategy());
	else if (random == 1)
		p.setStrategy(new DefensiveStrategy());
	else
		p.setStrategy(new RandomStrategy());
	AIPlayers.push_back(p);
}

void GameState::changeGamePhase(Phase newPhase) {

}

void GameState::updatePlayerTurn() {

}
Player* GameState::getCurrentPlayer() {
	// TODO : Create actual method, this is just to prevent error when compiling
	return new Player();
}
Player GameState::getMainPlayer() {
	return player;
}
vector<Player> GameState::getAIPlayers() {
	
	vector<Player> copy = AIPlayers;
	return copy;

}
void GameState::setMap(string name) {
	map = Map(); // TODO use the name
}

void GameState::generateCountries() {
	/*
	Assign a number of countries for the player and then for the AI players
	*/
}

//template<class Archive>
//void GameState::serialize(Archive & archive) {
//	archive(currentPlayerTurn);
//}