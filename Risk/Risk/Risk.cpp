// Risk.cpp : Defines the entry point for the console application.
//
#pragma once
#include <iostream>
#include <string>
#include "Engine.h"
#include "stdafx.h"

void player_testing() {
	Player p1("Justin");
	std::cout << p1.get_player_name() + " currently owns: " + p1.print_countries_owned() << std::endl;
	p1.view_hand(); //Possibly refactor this to return a string?
}

void country_testing() {
	Player p1("Eric");
	std::cout << p1.get_player_name() + " currently owns: " + p1.print_countries_owned() << std::endl;

	Country c1("Canada");
	Country c2("USA");
	Country c3("Mexico");

	p1.assign_country(c1);
	p1.assign_country(c2);
	p1.assign_country(c3);
	std::cout << p1.get_player_name() + " currently owns: " + p1.print_countries_owned() << std::endl;

	Player p2("Amanda");
	p2.assign_country(c1);
	std::cout << p1.get_player_name() + " currently owns: " + p1.print_countries_owned() << std::endl;
	std::cout << p2.get_player_name() + " currently owns: " + p2.print_countries_owned() << std::endl;

	p2.remove_country(c1);
	std::cout << p1.get_player_name() + " currently owns: " + p1.print_countries_owned() << std::endl;
	std::cout << p2.get_player_name() + " currently owns: " + p2.print_countries_owned() << std::endl;

	p1.remove_country(c1);
	p2.assign_country(c1);
	std::cout << p1.get_player_name() + " currently owns: " + p1.print_countries_owned() << std::endl;
	std::cout << p2.get_player_name() + " currently owns: " + p2.print_countries_owned() << std::endl;
}

void deck_testing() {
	Player p1("Michael");
	Deck deck;
	Deck::Card card0;
	card0.card_id = 3;
	deck.return_card(card0);
	Deck::Card card1 = deck.draw_card();
	deck.return_card(card1);
	p1.view_hand();
	p1.add_to_hand(deck.draw_card());
	p1.add_to_hand(deck.draw_card());
	p1.view_hand();
}

void card_cashing_testing() {
	Player p1("Kyle");
	Deck deck;
	for (int i = 0; i<10; i++) {
		p1.add_to_hand(deck.draw_card());
	}
	p1.view_hand();
	p1.cash_cards(deck);
	p1.view_hand();
}

void combat_testing() {
	std::srand(unsigned(std::time(0)));
	Player p1("Andrew");
	Player p2("Meghan");
	Country c1("Canada");
	Country c2("USA");
	p1.assign_country(c1);
	p2.assign_country(c2);
	c1.increment_armies(40);
	c2.increment_armies(30);
	Combat::combat(c1, c2, true, 0, 0, 0);
	std::cout << p1.get_player_name() + " currently owns: " + p1.print_countries_owned() << std::endl;
	std::cout << p2.get_player_name() + " currently owns: " + p2.print_countries_owned() << std::endl;
	std::cout << c1.get_country_name() + " currently has " << c1.get_number_of_armies() << " armies." << std::endl;
	std::cout << c2.get_country_name() + " currently has " << c2.get_number_of_armies() << " armies." << std::endl;
	system("pause");
}

void saveLoad_testing() {
	SaveLoadManager slm;
	//GameState gs("Eric");
	//slm.SaveGame(gs);
	slm.LoadGame("gameSave.xml");
}

void map_testing() {
	MapTester mt;
	mt.TestMapCreation();
}


void game_state_testing() {
	Player p1("Michonne");
	Country c1("Germany");
	Country c2("France");
	Country c3("South Africa");
	p1.assign_country(c1);
	p1.assign_country(c2);
	p1.assign_country(c3);
	c1.increment_armies(7);
	c2.increment_armies(5);
	c3.increment_armies(3);
	//GameState g;
	//g.reinforcingPhase();
	//GameState g;
	//g.displayMapDirectoryContents();
	//g.reinforcingPhase(p1);
	
}

void mapObserverTesting() {
	MapObserver mo;
	Country c("Canada");
	c.registerObserver(&mo);
	c.increment_armies(5);
	c.decrement_armies(3);
	c.set_continent_name("North America");
	
}
void playerObserverTesting() {
	
	// create a players to be observed
	Player *bob= new Player("bob");
	Player *meg = new Player("megan");
	//create a playerview that is connected to the player
	playerView * pvb = new playerView(bob);
	playerView * pvm = new playerView(meg);
	// attach playerviews to each other
	bob->Attach(pvm);
	meg->Attach(pvb);
	
	// Create continents
	Continent NorthAmerica("North America", 1, 5);
	Continent Europe("Europe", 2, 6);
	

	// create countries to be added to players
	
	Country c1( "germany" ,Europe);
	Country c2("France",Europe);
	Country c3("USA",NorthAmerica);
	Country c4("Canada",NorthAmerica);
	//add countries to countrie
	vector<Country*> NA;
	NA.push_back(&c3);
	NA.push_back(&c4);
	vector<Country*> EU;
	EU.push_back(&c2);
	EU.push_back(&c1);

	// assign countries to continents
	NorthAmerica.setContainedCountries(NA);
	Europe.setContainedCountries(EU);
	// assign countries to players
	bob->assign_country(c4);
	meg->assign_country(c2);

	cout << endl << " NA will be completed" << endl;

	bob->assign_country(c3);
	// increment armies in countries of a player
	cout << endl<< "incrementation of armies";
	bob->get_country(0)->increment_armies(5);
	bob->get_country(1)->increment_armies(7);
	meg->get_country(0)->increment_armies(3);

	// decrement armies in countries of player
	bob->get_country(1)->decrement_armies(1);
	meg->get_country(0)->decrement_armies(2);
	
	// add one more country to meg and assign armies
	c4.increment_armies(3);
	meg->assign_country(c1);

	// increment battles won
	cout << endl << "increment battles won" << endl;
	meg->incrementBattlesWon();


	

}


// fuctions used in Demo
// almost all if not all the returns are going to have to be changed to either return a map or a list of maps 
//ive done it this way for testing as i go.
void newMap() {
	cout << "Create new map chosen. \n";
}
void showListOfMaps() {
	cout << "Show list of maps chosen. \n";
	//display

}
void displayOthers() {
	cout << "Display other existing maps chosen. \n";
	//show list of maps
	showListOfMaps();
	// map is chosen to load
	int userInput = 0;
	cout << "please choose map from list above (if your input doesn't match one of the possible integers default map will be loaded) : \n";
	cin >> userInput;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "\n value inputed not of type int. please try again. \n";
		cin >> userInput;
	};

}
void playDefault() {
	cout << "Play default chosen \n";
	//load default map
}
void loadMap() {
	cout << "Load map chosen. \n";
	cout << "Please enter the number corresponding to your choice: \n1. Play default map \n2. Display other existing maps \n";
	int userInput = 0;
	bool valid = false;
	while (valid == false) {
		userInput = InputProcedure::get_choice();
		if (userInput == 1 || userInput == 2) {
			valid = true;
		}
		else { std::cout << "Not a valid choice." << std::endl; }
	}
	if (userInput == 1) { playDefault(); }
	else displayOthers();
}

void editMap() {
	cout << "Edit map chosen. \n";
	cout << "Please enter the number corresponding to your choice: \n1. New map \n2. Edit an exising map \n";
	int userInput = 0;
	bool valid = false;
	while (valid == false) {
		userInput = InputProcedure::get_choice();
		if (userInput == 1 || userInput == 2) {
			valid = true;
		}
		else { std::cout << "Not a valid input." << std::endl; }
	}
	if (userInput == 1) { newMap(); }
	else displayOthers();
}

void mapCreationPhase() {
	cout << "Please enter the number corresponding to your choice: " << endl << endl << "1. Load map \n" << "2. Map editor \n";
	int userInput = 0;
	bool valid = false;
	while (valid == false) {
		userInput = InputProcedure::get_choice();
		if (userInput == 1 || userInput == 2) {
			valid = true;
		}
		else { std::cout << "Not a valid input" << std::endl; }
	}
	if (userInput == 1) { loadMap(); }
	else editMap();
}


void Demo() {
	cout << "Welcome to the game of Risk. " << endl << endl;
	mapCreationPhase();
}
void GameLifeTest() {
	Engine* e = new Engine();
}
int _tmain(int argc, _TCHAR* argv[])
{
	//TODO: uncomment
	//std::cout << "PLAYER TESTING" << std::endl;
	//player_testing();

	//std::cout << "\nCOUNTRY TESTING" << std::endl;
	//country_testing();
	//system("pause");

	//std::cout << "\nDECK TESTING" << std::endl;
	//deck_testing();

	//std::cout << "\nCARD CASHING TESTING" << std::endl;
	//card_cashing_testing();

	//std::cout << "\nCOMBAT TESTING" << std::endl;
	//combat_testing();

	//saveLoad_testing();

	//map_testing();
	
	//game_state_testing();
	
	//mapObserverTesting();

	//combat_testing();
	
	GameLifeTest();
	
	//playerObserverTesting();
	//Demo();

	system("pause");

	return 0;
}
