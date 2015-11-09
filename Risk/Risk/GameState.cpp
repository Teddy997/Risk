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
	else if (currentPhase == FORTIFYING) {
		fortifyingPhase();
	}
}
void GameState::fortifyingPhase() {

	cout << "**********FORTIFYING PHASE*************" << endl;
	//updateView();
	if (currentPlayer == player) {
		cout << "Here are the countries that you own and their connections( which you also own) :" << endl;
		vector<Country*> countriesOwned = currentPlayer->getCountries();
		for (int i = 0; i < countriesOwned.size(); ++i) {
			bool hasAtLeastOne = false;
			cout << i + 1 << ". Country: " << countriesOwned[i]->get_country_name()
				<< ", Armies: " << countriesOwned[i]->get_number_of_armies()
				<< ", friendly connected countries: ";
			vector<Country*> countriesConnected = countriesOwned[i]->getConnectedCountries();
			for (int j = 0; j < countriesConnected.size(); ++j) {

				if (countriesConnected[j]->getOwner() == player) {
					cout << " \"" << countriesConnected[j]->get_country_name() << "\"";
					hasAtLeastOne = true;
				}
			}
			if (hasAtLeastOne == false)
				cout << "none.";
			cout << endl;
			
		}


		cout << "\n****Enter the number of the country you'd like to move armies from." << endl;
		bool valid = false;
		while (valid == false) {
			int index = getIndexOfCountry()-1;

			Country* c = currentPlayer->get_country(index);
			vector<Country*> countriesConnected = c->getConnectedCountries();
			for (Country* c2 : countriesConnected) {
				if (c2->getOwner() == player) {
					valid = true;
				}
			}
			if (valid == false) {
				cout << "Sorry, you own the country that you selected, but there is no other country to fortify that is next to it."
					<< " Please pick again" << endl;
			}
			else {
				cout << "Now choose the index of the country to which you want to send armies to :" << endl;
				int index2 = getIndexOfCountry()-1;
				Country* connected = currentPlayer->get_country(index2);
				if (find(countriesConnected.begin(),countriesConnected.end(),connected) != countriesConnected.end()) {
					cout << "Enter how many armies you want to move " << endl;
					int armies = getArmies(c->get_number_of_armies());
					connected->increment_armies(armies);
					c->decrement_armies(armies);
					valid = true;
				}
				else {
					valid = false;
					cout << "Invalid choice, please choose a country that is connected to your previous choice." << endl;
					cout << "Please enter the number of the country you'd like to move armies from." << endl;
				}
			}
		}

		
	}
	else {
		doAIFortification();
	}




	updateView();
}
void GameState::doAIFortification() {

}
void GameState::setPlayerTurn(Player* p) {
	currentPlayer = p;
}
void GameState::reinforcingPhase() {
	int armiesAwarded = currentPlayer->numberOfCountriesOwned() / 3;
	if (armiesAwarded < 3) { armiesAwarded = 3; }
	cout << endl;
	cout << currentPlayer->get_player_name() << " has " << armiesAwarded << " armies to place." << endl;
	updateView();
	if (currentPlayer == player) { // will do the human player first, else will do the AI reinforcement
		while (armiesAwarded > 0) {
			
		
				cout << "Enter the number of the country you'd like to reinforce." << endl;
				int index = getIndexOfCountry();
				cout << "Enter the number of armies you'd like to reinforce with." << endl;

				int armies = getArmies(armiesAwarded);
				currentPlayer->get_country(index - 1)->increment_armies(armies);

				armiesAwarded -= armies;
				
			}
		}	else {
		doAIReinforcement(armiesAwarded);

	}
	updateView();
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
void GameState::updateView() {
		cout << "\n**********CURRENT COUNTRIES OF " << currentPlayer->get_player_name() << " **********" << endl;
		cout << currentPlayer->print_countries_owned() << endl;
	

}
int GameState::getArmies(int max) {
	bool valid_amount = false;
	int armies = 0;
	while (valid_amount == false) {
		int armiesDeducted = 0;
		armies = InputProcedure::get_choice();
		if (armies > max || armiesDeducted < 0) {
			cout << "Not a valid amount" << endl;
		}
		else {
			valid_amount = true;
		}
	}
	return armies;

}
int GameState::getIndexOfCountry() {
	int index = 1;
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
	return index;
}
//template<class Archive>
//void GameState::serialize(Archive & archive) {
//	archive(currentPlayerTurn);
//}