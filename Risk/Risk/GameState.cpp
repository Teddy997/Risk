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
	if (newPhase == REINFORCING) {
		//reinforcingPhase(currentPlayer);
	}
}

void GameState::reinforcingPhase(Player &currentPlayer) {
	int armiesAwarded = currentPlayer.numberOfCountriesOwned() / 3;
	if (armiesAwarded < 3) { armiesAwarded = 3; }

	std::cout << "\n**********CURRENT COUNTRIES**********" << std::endl;
	std::cout << currentPlayer.print_countries_owned() << std::endl;

	while (armiesAwarded > 0) {
		std::cout << currentPlayer.get_player_name() << " has " << armiesAwarded << " armies to place." << std::endl;
		std::cout << "Enter the number of the country you'd like to reinforce." << std::endl;
		int index;
		bool valid_country = false;
		while (valid_country == false) {
			index = InputProcedure::get_choice();
			if (index - 1 < 0 || index - 1 > currentPlayer.numberOfCountriesOwned() - 1) {
				std::cout << "Not a valid choice." << std::endl;
			}
			else {
				valid_country = true;
			}
		}
		std::cout << "Enter the number of armies you'd like to reinforce with." << std::endl;
		bool valid_amount = false;
		while (valid_amount == false) {
			int armiesDeducted = 0;
			armiesDeducted = InputProcedure::get_choice();
			if (armiesDeducted > armiesAwarded || armiesDeducted < 0) {
				std::cout << "Not a valid amount" << std::endl;
			}
			else {
				currentPlayer.get_country(index-1)->increment_armies(armiesDeducted);
				
				std::cout << "\n**********CURRENT COUNTRIES**********" << std::endl;
				std::cout << currentPlayer.print_countries_owned() << std::endl;

				armiesAwarded -= armiesDeducted;
				valid_amount = true;
			}
		}
	}
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