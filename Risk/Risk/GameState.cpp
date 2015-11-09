#pragma once
#include "stdafx.h"
#include "GameState.h"
#include "tinydir.h"

GameState::GameState() {
	player = new Player();
	currentPlayer = player;
}

GameState::GameState(string name) {
	player = new Player(name);
	currentPlayer = player;
}


GameState::~GameState()
{
}

void GameState::addPlayer(string name) {
	Player* p = new Player(name);
	int random = rand() % 3;
	if (random == 0)
		p->setStrategy(new AgressiveStrategy());
	else if (random == 1)
		p->setStrategy(new DefensiveStrategy());
	else
		p->setStrategy(new RandomStrategy());
	AIPlayers.push_back(p);
}

void GameState::changeGamePhase(Phase newPhase) {
	currentPhase = newPhase;
	if (currentPhase == REINFORCING) {
		reinforcingPhase();
	}
}
void GameState::setPlayerTurn(Player* p) {
	currentPlayer = p;
}
void GameState::reinforcingPhase() {
	int armiesAwarded = currentPlayer->numberOfCountriesOwned() / 3;
	if (armiesAwarded < 3) { armiesAwarded = 3; }
	cout << endl;
	cout << currentPlayer->get_player_name() << " has " << armiesAwarded << " armies to place." << endl;
	cout << "\n**********CURRENT COUNTRIES OF " << currentPlayer->get_player_name() << " **********" << endl;
	cout << currentPlayer->print_countries_owned() << endl;
	if (currentPlayer == player) { // will do the human player first, else will do the AI reinforcement
		while (armiesAwarded > 0) {
			
		
				cout << "Enter the number of the country you'd like to reinforce." << endl;
				int index;
				bool valid_country = false;

				while (valid_country == false) {
					index = InputProcedure::get_choice();
					if (index - 1 < 0 || index - 1 > currentPlayer->numberOfCountriesOwned() - 1) {
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
						currentPlayer->get_country(index - 1)->increment_armies(armiesDeducted);

						armiesAwarded -= armiesDeducted;
						valid_amount = true;
					}
				}
			}
		}	else {
		doAIReinforcement(armiesAwarded);

	}
	cout << "\n**********CURRENT COUNTRIES OF " << currentPlayer->get_player_name() << " **********" << endl;
	cout << currentPlayer->print_countries_owned() << endl;
}
void GameState::doAIReinforcement(int armies) {
	while (armies != 0) {
		// cout << "Possible source of error: index of country chosen wrong" << endl;
		// random armies from the total pool of armies
		int armiesDeducted = rand() % armies + 1;
		armies -= armiesDeducted;
		// choose a random country to reinforce
		int index = rand() % currentPlayer->numberOfCountriesOwned();
		currentPlayer->get_country(index)->increment_armies(armiesDeducted);
		cout << "******* " << currentPlayer->get_player_name() << " has chosen to reinforce "
			<< currentPlayer->get_country(index)->get_country_name()
			<< " with " << armiesDeducted << " armies.******" << endl;
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
Player* GameState::getCurrentPlayer() {
	return currentPlayer;
}
Player* GameState::getMainPlayer() {
	return player;
}
vector<Player*> GameState::getAIPlayers() {
	
	vector<Player*> copy;
	for (int i = 0; i < AIPlayers.size(); ++i) {
		Player* p = AIPlayers.at(i);
		copy.push_back(p);
	}
	return copy;

}
void GameState::setMap(string name) {
	map = new Map(); // TODO use the file names to load
}

void GameState::displayMapDirectoryContents() {
	string display = "";
	tinydir_dir dir;
	tinydir_open(&dir, "Maps");

	while (dir.has_next)
	{
		tinydir_file file;
		tinydir_readfile(&dir, &file);
		string filename = file.name;
		if (filename.compare("Thumbs.db") == 0 || filename.compare(".") == 0 || filename.compare("..") == 0) {
			display += "";
		}
		else {
			if (file.is_dir && (filename.compare("default") != 0))
			{
				display += filename;
				display += "\n";
			}
			else {
				display += "";
			}
		}
		tinydir_next(&dir);
	}

	tinydir_close(&dir);
	if (display.length() == 0) {
		cout << "There are currently no user created maps!" << endl;
	}
	else {
		cout << display << endl;
	}
}

void GameState::assignCountries() { 
	vector<Country*> countries = map->getCountries();
	int totalNbCountries = countries.size();
	int numberOfPlayers = 1 + AIPlayers.size();
	int numCountriesPerPlayer = totalNbCountries / numberOfPlayers;
	// if we don't have a perfect division, give the rest of the countries to the human player
	int extraCountries = totalNbCountries % numberOfPlayers;
	int numberOfArmiesPerPlayer = 0;
	if (numberOfPlayers == 2)
		numberOfArmiesPerPlayer = 40;
	else if (numberOfPlayers == 3)
		numberOfArmiesPerPlayer = 35;
	else if (numberOfPlayers == 4)
		numberOfArmiesPerPlayer = 30;
	

	// assign countries to players
	for (Country* c : countries) {
		int toPlayer = rand() % numberOfPlayers; 
		if (toPlayer == 0) {
			player->assign_country(*c);
		}
		else {
			--toPlayer;
			AIPlayers[toPlayer]->assign_country(*c);
		}
	}
	player->assignArmies(numberOfArmiesPerPlayer);
	// assign number of armies to each country 
	for (Player* p : AIPlayers) {
		p->assignArmies(numberOfArmiesPerPlayer);

		
	}
	

}

//template<class Archive>
//void GameState::serialize(Archive & archive) {
//	archive(currentPlayerTurn);
//}