#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>

#include <cereal/archives/xml.hpp>
#include <cereal/types/vector.hpp>
#include "Country.h"
#include "Deck.h"
#include "Strategy.h"
#include "subject.h"

class Strategy; // forward declaration

class Player : public Subject {
private:
	/*Member variables*/
	
	std::string player_name;
	std::vector<Country*> countries_owned;
	std::vector<Continent*> continents_owned;
	int total_continent_bonus;
	Strategy* strategy;

	void update_bonus();

	/*May possible have to refactor the hand logic to be a vector of pointers, similar to Country*/
	std::vector<Deck::Card> hand;
public:
	Player();
	Player(std::string name);
	~Player();
	std::string get_player_name();
	void setStrategy(Strategy* str);
	void executeStrategy(Player* p);
	void assign_country(Country& country);
	void remove_country(Country& country);
	std::string print_countries_owned();
	Country* get_country(int index);
	void set_total_bonus(int bonus) { total_continent_bonus += bonus; }
	int numberOfCountriesOwned();
	void assignArmies(int x);
	void add_to_hand(Deck::Card);
	void cash_cards(Deck& deck);
	void view_hand();

	template<class Archive>
	void serialize(Archive & archive) {archive(
		CEREAL_NVP(player_name));
	};

};

#endif