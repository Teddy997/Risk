#pragma once
#include "stdafx.h"
#include "GameState.h"

GameState::GameState() {

}
GameState::GameState(string name)
{
	player = Player(name);
	currentPlayer = player;
}


GameState::~GameState()
{
}

void GameState::addPlayer(string name) {
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
	currentPhase = newPhase;
	if (currentPhase == REINFORCING) {
		reinforcingPhase();
	}
}
void GameState::setPlayerTurn(Player p) {
	currentPlayer = p;
}
void GameState::reinforcingPhase() {
	int armiesAwarded = currentPlayer.numberOfCountriesOwned() / 3;
	if (armiesAwarded < 3) { armiesAwarded = 3; }

	cout << "\n**********CURRENT COUNTRIES**********" << endl;
	cout << currentPlayer.print_countries_owned() << endl;

	while (armiesAwarded > 0) {
		cout << currentPlayer.get_player_name() << " has " << armiesAwarded << " armies to place." << endl;
		if (&currentPlayer == &player) { // will do the human player first, else will do the AI reinforcement
			cout << "Enter the number of the country you'd like to reinforce." << endl;
			int index;
			bool valid_country = false;

			while (valid_country == false) {
				index = InputProcedure::get_choice();
				if (index - 1 < 0 || index - 1 > currentPlayer.numberOfCountriesOwned() - 1) {
					cout << "Not a valid choice." << endl;
				}
				else {
					valid_country = true;
				}
			}
			cout << "Enter the number of armies you'd like to reinforce with." << endl;
			bool valid_amount = false;
			while (valid_amount == false) {
				int armiesDeducted = 0;
				armiesDeducted = InputProcedure::get_choice();
				if (armiesDeducted > armiesAwarded || armiesDeducted < 0) {
					cout << "Not a valid amount" << endl;
				}
				else {
					currentPlayer.get_country(index - 1)->increment_armies(armiesDeducted);

					cout << "\n**********CURRENT COUNTRIES**********" << endl;
					cout << currentPlayer.print_countries_owned() << endl;

					armiesAwarded -= armiesDeducted;
					valid_amount = true;
				}
			}
		}
		else {
			doAIReinforcement(armiesAwarded);
		}
	}
}
void GameState::doAIReinforcement(int armies) {
	while (armies != 0) {
		// cout << "Possible source of error: index of country chosen wrong" << endl;
		// random armies from the total pool of armies
		int armiesDeducted = rand() % armies + 1;
		armies -= armiesDeducted;
		// choose a random country to reinforce
		int index = rand() % currentPlayer.numberOfCountriesOwned();
		currentPlayer.get_country(index)->increment_armies(armiesDeducted);
	}
}


void GameState::updatePlayerTurn(int turn) {
	if (turn == 1)
		currentPlayer = player;
	else {
		int t = turn - 2;
		for (unsigned int i = 0; i < AIPlayers.size(); ++i) {
			if (t == i)
				currentPlayer = AIPlayers[i];
		}
	}
}
Player GameState::getCurrentPlayer() {
	return currentPlayer;
}
Player GameState::getMainPlayer() {
	return player;
}
vector<Player> GameState::getAIPlayers() {
	
	vector<Player> copy = AIPlayers;
	return copy;

}
void GameState::setMap(string name) {
	map = Map(); // TODO use the file names to load
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