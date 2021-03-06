#pragma once
#include <algorithm>
#include <sstream>
#include "GameState.h"
#include "tinydir.h"

GameState::GameState() {
	player = new Player();
	currentPlayer = player;
	currentPlayer->setStrategy(new NoStrategy());
	deck = new Deck;
}

GameState::GameState(string name) {
	
	player = new Player(name);
	currentPlayer = player;
	currentPlayer->setStrategy(new NoStrategy());
	deck = new Deck;
	manageMap();
}

GameState::GameState(bool loading, string line) {
	if (loading == true) {
		cout << "LOADING" << endl;
		build(line);
	}
}


GameState::~GameState()
{
}
void GameState::manageMap() {

	cout << "Do you want to jump straight in the game by choosing a map or do you want to proceed to the map creator? "
		<< "Select the index of choice you want" << endl;
	cout << "1. I want to jump straight in the game by choosing a map.  2. I want to go to the map editor." << endl;
	cout << "3. I want to load an existing game." << endl;
	int index = 1;
	bool valid = false;
	brandNewGame = true;
	while (valid == false) {

		index = InputProcedure::get_choice();
		
		if (index < 1 || index > 3) {
			cout << "Not a valid choice." << endl;
		}
		else {
			valid = true;
		}

	}
	if (index == 2) {
		MapCreator mapCreator = MapCreator();
		mapCreator.Create_map();
	}
	if (index == 3) {
		brandNewGame = false;
		cout << "Please type the name of the game you wish to load." << endl;
		displaySaveDirectoryContents();
	}
}

void GameState::setPlayer(Player* p) {
	player = p;
	player->setStrategy(new NoStrategy());
}

void GameState::setAIPlayers(std::vector<Player*> ais) {
	AIPlayers.clear();
	for (int i = 0; i < ais.size(); i++) {
		AIPlayers.push_back(ais.at(i));
	}
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
		
	//p->setStrategy(new AgressiveStrategy());			//OK
	//p->setStrategy(new DefensiveStrategy());			//OK			
	//p->setStrategy(new RandomStrategy());				//OK
	cout << p->get_player_name() << " has type of strategy: " << p->getStrategy()->getStratName() << endl;
	AIPlayers.push_back(p);
	
}
void GameState::changeStrategy() {
	cout << "Do you wish to change any of the player's attack strategy? (y/n)" << endl;
	string s;
	cin >> s;
	if (s == "y") {
		for (Player* p : AIPlayers) {
			cout << p->get_player_name() << " has type of strategy: " << p->getStrategy()->getStratName() << endl;
			cout << "Change their strategy? (y/n)" << endl;
			string ss;
			cin >> ss;
			if (ss == "y") {
				cout << "Type in the number of any of the following: " << endl;
				cout << "1. Agressive\n2. Defensive\n3. Random" << endl;
				bool valid_amount = false;
				int strat = 0;
				while (valid_amount == false) {
					
					strat = InputProcedure::get_choice();
					if (strat <= 0 || strat > 3) {
						cout << "Not a valid amount" << endl;
					}
					else {
						valid_amount = true;
					}
				}
				if (strat == 1)
					p->setStrategy(new AgressiveStrategy());
				else if (strat == 2)
					p->setStrategy(new DefensiveStrategy());
				else if (strat == 3)
					p->setStrategy(new RandomStrategy());
			}
		}
	}
}
void GameState::attackingPhase() {
	cout << "**********ATTACKING PHASE*************\n" << endl;
	cout << currentPlayer->get_player_name() << " is currently attacking...\n" << endl;
	updateView();
	if (currentPlayer == player) {
		doPlayerAttacking();
	}
	else {
		doAIAttacking();
	}
	updateView();
}

void GameState::displayAttackOptions() {
	cout << "Here are the countries that you own and their connected enemy countries :" << endl;
	vector<Country*> countriesOwned = currentPlayer->getCountries();
	for (unsigned int i = 0; i < countriesOwned.size(); ++i) {
		bool hasAtLeastOne = false; // at least one connection
		cout << i + 1 << ". Country: " << countriesOwned[i]->get_country_name()
			<< ", Armies: " << countriesOwned[i]->get_number_of_armies()
			<< ", enemy connected countries and their army count: ";
		vector<Country*> countriesConnected = countriesOwned[i]->getConnectedCountries();
		for (unsigned int j = 0; j < countriesConnected.size(); ++j) {

			if (countriesConnected[j]->getOwner() != player) {
				cout << " \"" << countriesConnected[j]->get_country_name() << ":" << countriesConnected[j]->get_number_of_armies() << "\"";
				hasAtLeastOne = true;
			}
		}
		if (hasAtLeastOne == false)
			cout << "none.";
		cout << endl;

	}
	cout << "\n****Enter the number of the country you'd like to attack from. If you do not want to attack"
		<< ", please enter -1 to go to the next phase." << endl;
}
void GameState::doPlayerAttacking() {

	displayAttackOptions();

	bool valid = false;
	bool v = false;
	while (valid == false) {
		int index = getIndexOfCountry() - 1;

		if (index + 1 == -1)
			break;
		Country* c = currentPlayer->get_country(index);
		vector<Country*> countriesConnected = c->getConnectedCountries();
		for (Country* c2 : countriesConnected) {
			if (c2->getOwner() != player) {
				v = true;
			}
		}
		if (v == false) {
			cout << "Sorry, you own the country that you selected, but there is no other country to attack that is next to it."
				<< " Please pick again" << endl;
		}
		else {
			cout << "Now type in the name correctly(lower case and upper case) of the country you want to attack :" << endl;
			string name;
			bool valid2 = false;
			getline(cin, name);
			//int index2 = getIndexOfCountry() - 1;
			Country* connected;
			//find the country
			for (Player* p : AIPlayers) {
				vector<Country*> countriesOfAI = p->getCountries();

				for (Country* cc : countriesOfAI) {
					if (name == cc->get_country_name()) {
						valid2 = true;
						connected = cc;
					}
					if (valid2)
						break;
				}
				if (valid2)
					break;
			}
			if (find(countriesConnected.begin(), countriesConnected.end(), connected) != countriesConnected.end() && valid2) {
				//cout << "COMBATTTTTTTTTTTTTTING" << endl;
				Combat::combat(*c, *connected, true, 0, 0, 0);

				cout << endl;
				displayAttackOptions();
			}
			// checks if the country he owned is part of the vector of connected countries of the first countries

				/*
				cout << "Enter how many armies you want to move " << endl;
				int armies = getArmies(c->get_number_of_armies());
				if (c->get_number_of_armies() == armies) {
					valid = false;
					cout << "Sorry, you cannot move all the armies you have in that country. A country must always have at least 1 army." << endl;
					cout << "Please enter the number of the country you'd like to move armies from." << endl;
				}*/
			/*
				else {


					connected->increment_armies(armies);
					c->decrement_armies(armies);
					valid = true;
				}
				*/
			//}
			else {
				valid = false;
				cout << "Invalid choice, please choose a country that is connected to your previous choice." << endl;
				cout << "Please enter the number of the country you'd like to attack from." << endl;
			}
		}
	}


}
void GameState::doAIAttacking() {
	
	currentPlayer->executeStrategy(player);
	for (Player* p2 : AIPlayers) {
		
		if (currentPlayer != p2) {
				currentPlayer->executeStrategy(p2);
		}
	}
}

void GameState::changeGamePhase(Phase newPhase) {
	currentPhase = newPhase;
	if (currentPhase == REINFORCING) {
		reinforcingPhase();
	}
	else if (currentPhase == FORTIFYING) {
		fortifyingPhase();
	}
	else if (currentPhase == ATTACKING) {
		attackingPhase();
	}
}
void GameState::fortifyingPhase() {
	// this method contains so many lines of code only because we assume that the user may not enter what is required
	// and handles all or most of those cases
	cout << "**********FORTIFYING PHASE*************\n" << endl;
	cout << currentPlayer->get_player_name() << " is currently fortifying...\n" << endl;
	//updateView();
	// do this whole chunk of code if it's the user's turn
	if (currentPlayer == player) {
		doPlayerFortification();
	}
	else {
		doAIFortification();
	}



	
	updateView();
}

void GameState::doPlayerFortification() {
	cout << "Here are the countries that you own and their connections( which you also own) :" << endl;
	vector<Country*> countriesOwned = currentPlayer->getCountries();
	for (unsigned int i = 0; i < countriesOwned.size(); ++i) {
		bool hasAtLeastOne = false; // at least one connection
		cout << i + 1 << ". Country: " << countriesOwned[i]->get_country_name()
			<< ", Armies: " << countriesOwned[i]->get_number_of_armies()
			<< ", friendly connected countries: ";
		vector<Country*> countriesConnected = countriesOwned[i]->getConnectedCountries();
		for (unsigned int j = 0; j < countriesConnected.size(); ++j) {

			if (countriesConnected[j]->getOwner() == player) {
				cout << " \"" << countriesConnected[j]->get_country_name() << "\"";
				hasAtLeastOne = true;
			}
		}
		if (hasAtLeastOne == false)
			cout << "none.";
		cout << endl;

	}
	// so far we've only displayed a message.

	cout << "\n****Enter the number of the country you'd like to move armies from. If you do not want to fortify"
		<< ", please enter -1 to stop fortifying." << endl;
	bool valid = false;
	while (valid == false) {
		int index = getIndexOfCountry() - 1;

		if (index + 1 == -1)
			break;
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
			int index2 = getIndexOfCountry() - 1;
			Country* connected = currentPlayer->get_country(index2);
			// checks if the country he owned is part of the vector of connected countries of the first countries
			if (find(countriesConnected.begin(), countriesConnected.end(), connected) != countriesConnected.end()) {
				cout << "Enter how many armies you want to move " << endl;
				int armies = getArmies(c->get_number_of_armies());
				if (c->get_number_of_armies() == armies) {
					valid = false;
					cout << "Sorry, you cannot move all the armies you have in that country. A country must always have at least 1 army." << endl;
					cout << "Please enter the number of the country you'd like to move armies from." << endl;
				}
				else {


					connected->increment_armies(armies);
					c->decrement_armies(armies);
					valid = true;
				}

			}
			else {
				valid = false;
				cout << "Invalid choice, please choose a country that is connected to your previous choice." << endl;
				cout << "Please enter the number of the country you'd like to move armies from." << endl;
			}
		}
	}


}
void GameState::doAIFortification() {
	cout << "The AI algorithm will fortify countries randomly" << endl;
	bool done = false;
	int numberOfTries = 0; // to make sure that this while loop exits after number of tries in case the AI has nowhere to fortify
	while (!done && numberOfTries < 200) {
		++numberOfTries;
		// choose random country from where to fortify
		int index = rand() % currentPlayer->numberOfCountriesOwned();
		Country* c1 = currentPlayer->get_country(index);
		int armiestoMove = 0;
		bool validMove = true;
		if (c1->get_number_of_armies() > 1)
			armiestoMove = rand() % (c1->get_number_of_armies() - 1) + 1;
		else
			validMove = false;
		if (validMove) {
			// choose random country to which to move
			if (c1->getConnectedCountries()[0] != NULL) {
				int index2 = rand() % c1->getConnectedCountries().size();
				Country* c2 = c1->getConnectedCountries()[index2];
				if (c2->getOwner() == currentPlayer) {
					c1->decrement_armies(armiestoMove);
					c2->increment_armies(armiestoMove);
					cout << currentPlayer->get_player_name() << " has chosen to fortify "
						<< c2->get_country_name() << " from " << c1->get_country_name()
						<< " with " << armiestoMove << "." << endl;
					done = true;
				}
				else {
					done = false;
				}
			}
			else
				done = false;
		}
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
				currentPlayer = AIPlayers.at(i);
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
	for (unsigned int i = 0; i < AIPlayers.size(); ++i) {
		Player* p = AIPlayers.at(i);
		copy.push_back(p);
	}
	return copy;

}
void GameState::setMap(string name) {
	map = new Map(name); // TODO use the file names to load
	cout << map->nbOfCountries() << endl;
}

void GameState::setMap(MapTemplate mapTemplate) {
	map = new Map(mapTemplate);
	cout << map->nbOfCountries() << endl;
}

void GameState::setMap(Map* m) {
	map = m;
	cout << map->nbOfCountries() << endl;
}

void GameState::displaySaveDirectoryContents() {
	string display = "";
	tinydir_dir dir;
	tinydir_open(&dir, "Saves");

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
				display += "";
			}
			else {
				for (int i = 0; i < filename.size(); i++) {
					if (i < filename.size() - 4) {
						display += filename[i];
					}
				}
				display += "\n";
			}
		}
		tinydir_next(&dir);
	}

	tinydir_close(&dir);
	if (display.length() == 0) {
		cout << "There are currently no existing save files!" << endl;
	}
	else {
		cout << display << endl;
	}
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
		cout << "There are currently no existing user created maps!" << endl;
	}
	else {
		cout << display << endl;
	}
}

void GameState::removePlayerAtIndex(int i) {
	currentPlayer = NULL;
	AIPlayers.erase(AIPlayers.begin() + i);


}

void GameState::assignCountries() { 
	vector<Country*> countries = map->getCountries();
	int numberOfPlayers = 1 + AIPlayers.size();
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
		if (index == -1)
			break;
		
		else if (index - 1 < 0 || index - 1 > currentPlayer->numberOfCountriesOwned() - 1) {
			cout << "Not a valid choice." << endl;
		}
		else {
			valid_country = true;
		}
		
	}
	return index;
}

void GameState::setupObservers() {
	playerView* pView1 = new playerView(player);
	for (int i = 0; i < AIPlayers.size(); i++) {
		playerView* pViewOthers = new playerView(AIPlayers.at(i));
	}
	cout << "Player observer initiated." << endl;
}

std::string GameState::phaseToString() {
	std::string phase;
	switch (currentPhase) {
	case REINFORCING:
		phase = "REINFORCING";
		break;
	case ATTACKING:
		phase = "ATTACKING";
		break;
	default:
		phase = "FORTIFYING";
		break;
	}
	return phase;
}

GameState::UnBuilder::UnBuilder(GameState* g) {
	UnBuilder::gs = g;
}

GameState::UnBuilder::~UnBuilder() { }

std::string GameState::UnBuilder::unbuild() {
	std::string unbuilt;
	
	std::string mapDirectoryInfo = UnBuilder::gs->getMap()->getMapDirectory();
	unbuilt += mapDirectoryInfo + "\n";
	unbuilt += "$\n";

	unbuilt += to_string(UnBuilder::gs->getAIPlayers().size()+1);
	unbuilt += "\n$\n";

	std::string mainPlayerInfo = UnBuilder::gs->getMainPlayer()->unbuild();
	unbuilt += mainPlayerInfo;
	unbuilt += "$\n";

	for (int i = 0; i < UnBuilder::gs->getAIPlayers().size(); i++) {
		std::string currentAIPlayerInfo = UnBuilder::gs->getAIPlayers().at(i)->unbuild();
		unbuilt += currentAIPlayerInfo;
		unbuilt += "$\n";
	}

	std::string currentPlayerInfo = UnBuilder::gs->getCurrentPlayer()->unbuild();
	unbuilt += currentPlayerInfo;
	unbuilt += "$\n";

	std::string phase = UnBuilder::gs->phaseToString();
	unbuilt += phase;
	unbuilt += "\n$\n";

	std::vector<Deck::Card> current_deck = UnBuilder::gs->getDeck()->get_current_deck();
	for (int i = 0; i < current_deck.size(); i++) {
		if (i != current_deck.size() - 1) {
			unbuilt += std::to_string(current_deck.at(i).card_id) + ",";
		}
		else {
			unbuilt += std::to_string(current_deck.at(i).card_id) + "\n$";
		}
	}

	return unbuilt;
}

std::string GameState::unbuild() {
	GameState::UnBuilder ub(this);
	return ub.unbuild();
}

GameState::Builder::Builder(std::string bp) {
	blueprint = bp;
}

void GameState::Builder::setMapName_tobuild(std::string line) {
	line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
	map_name_tobuild = line;
}

void GameState::Builder::setMap_tobuild() {
	map_tobuild = new Map(map_name_tobuild);
}

void GameState::Builder::setNumOfPlayers_tobuild(std::string line) {
	num_of_players_tobuild = stoi(line);
}

void GameState::Builder::setPlayer_tobuild(std::string line) {
	Player* temp = new Player();
	player_tobuild = temp->build(line, map_tobuild);
}

void GameState::Builder::setAIPlayers_tobuild(std::string line) {
	Player* temp = new Player();
	ai_players_tobuild.push_back(temp->build(line, map_tobuild));
}

void GameState::Builder::setCurrentPlayer_tobuild(std::string line) {
	std::vector<std::string> l = split(line, '\n');
	if (l.at(1).compare(player_tobuild->get_player_name()) == 0) {
		current_player_tobuild = player_tobuild;
	}
	else {
		for (int i = 0; i < ai_players_tobuild.size(); i++) {
			if (l.at(1).compare(ai_players_tobuild.at(i)->get_player_name()) == 0) {
				current_player_tobuild = ai_players_tobuild.at(i);
			}
		}
	}
}

void GameState::Builder::setCurrentPhase_tobuild(std::string line) {
	std::vector<std::string> l = split(line, '\n');
	if (l.at(1).compare("REINFORCING") == 0) {
		currentPhase_tobuild = REINFORCING;
	}
	else if (l.at(1).compare("ATTACKING") == 0) {
		currentPhase_tobuild = ATTACKING;
	}
	else { currentPhase_tobuild = FORTIFYING; }
}

void GameState::Builder::setCurrentDeck_tobuild(std::string line) {
	std::vector<std::string> l = split(line, ',');
	std::vector<Deck::Card> d;
	for (int i = 0; i < l.size(); i++) {
		Deck::Card c;
		c.card_id = std::stoi(l.at(i));
		d.push_back(c);
	}
	current_deck_tobuild = new Deck;
	current_deck_tobuild->set_deck(d);
}

GameState* GameState::Builder::build() {
	std::vector<std::string> contents = split(blueprint, '$');
	setMapName_tobuild(contents.at(0));
	setMap_tobuild();
	setNumOfPlayers_tobuild(contents.at(1));
	setPlayer_tobuild(contents.at(2));
	for (int i = 1; i < num_of_players_tobuild; i++) {
		setAIPlayers_tobuild(contents.at(2 + i));
	}
	setCurrentPlayer_tobuild(contents.at(contents.size()-4));
	setCurrentPhase_tobuild(contents.at(contents.size()-3));
	setCurrentDeck_tobuild(contents.at(contents.size()-2));

	GameState* gs = new GameState();
	gs->setMap(map_tobuild);
	gs->setPlayer(player_tobuild);
	gs->setAIPlayers(ai_players_tobuild);
	gs->setPlayerTurn(current_player_tobuild);
	gs->setGamePhase(currentPhase_tobuild);
	gs->setDeck(current_deck_tobuild);
	return gs;
}

std::vector<std::string> GameState::Builder::split(std::string s, char delim) {
	std::stringstream ss(s);
	std::string item;
	std::vector<string> items;
	while (std::getline(ss, item, delim)) {
		items.push_back(item);
	}
	return items;
}

GameState* GameState::build(std::string contents) {
	GameState::Builder b(contents);
	return b.build();
}
