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
	Combat::combat(c1, c2);
	std::cout << p1.get_player_name() + " currently owns: " + p1.print_countries_owned() << std::endl;
	std::cout << p2.get_player_name() + " currently owns: " + p2.print_countries_owned() << std::endl;
	std::cout << c1.get_country_name() + " currently has " << c1.get_number_of_armies() << " armies." << std::endl;
	std::cout << c2.get_country_name() + " currently has " << c2.get_number_of_armies() << " armies." << std::endl;
	system("pause");
}

void saveLoad_testing() {
	SaveLoadManager slm;
	slm.SaveGame();
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

void GameLifeTest() {
	Engine* e = new Engine();
	//cout << "wtf is going on" << endl;
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

	//GameLifeTest();

<<<<<<< HEAD
	//playerObserverTesting();
	
=======
	playerObserverTesting();
	system("pause");
>>>>>>> 7b9bad8f917ffb7be23046c483208c88555e0fff
	return 0;
}
