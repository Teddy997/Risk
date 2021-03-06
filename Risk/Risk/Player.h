#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include "Country.h"
#include "Deck.h"
#include "Strategy.h"
#include "subject.h"
#include "Map.h"

class playerView;

class Strategy; // forward declaration

class Player : public Subject {
private:
	/*Member variables*/
	
	std::string player_name;
	std::vector<Country*> countries_owned;
	std::vector<Continent*> continents_owned;
	int total_continent_bonus;
	int numberBattlesWon;
	Strategy* strategy;
	std::vector<playerView*> observers;

	void update_bonus();

	/*May possible have to refactor the hand logic to be a vector of pointers, similar to Country*/
	std::vector<Deck::Card> hand;
	int cardBonus;
	bool can_draw;

	class UnBuilder {
	private:
		class Player* pl;
	public:
		UnBuilder(Player* p);
		~UnBuilder();
		std::string unbuild();
	};

	class Builder {
	private:
		Map* map;
		std::string blueprint;
		std::string p_name_tobuild;
		std::vector<Country*> c_owned_tobuild;
		int numBattlesWon_tobuild;
		Strategy* strat;
		std::vector<Deck::Card> c_hand;
		int cardBonus;
		std::vector<std::string> split(std::string s);
		std::vector<std::string> split(std::string s, char d);
	public:
		Builder(std::string bp, Map* m);
		void set_p_name(std::string name);
		void set_cowned(std::string cowned);
		void set_numBattlesWon(std::string num);
		void set_Strategy(std::string stratName);
		void set_current_hand(std::string currentHand);
		void set_card_bonus(std::string amt);

		Player* build();
	};

public:
	Player();
	Player(std::string name);
	~Player();
	vector<Country*> getCountries() { return countries_owned; }
	std::string get_player_name();
	void setStrategy(Strategy* str);
	Strategy* getStrategy();
	void executeStrategy(Player* p2);
	void assign_country(Country& country);
	void remove_country(Country& country);
	std::string print_countries_owned();
	Country* get_country(int index);
	void set_total_bonus(int bonus) { total_continent_bonus += bonus; }
	int numberOfCountriesOwned();
	void assignArmies(int x);
	void assignCardBonusArmies(int amt);
	void incrementCardBonus();
	int const getCardBonus() { return cardBonus; }
	void setCardBonus(int amt) { cardBonus = amt; }
	void set_hand(std::vector<Deck::Card> h) { hand = h; }
	void set_can_draw(bool state) { can_draw = state; }
	bool const can_player_draw() { return can_draw; }
	void add_to_hand(Deck::Card);
	void cash_cards(Deck& deck);
	std::vector<Deck::Card> getHand() { return hand; }
	void view_hand();
	std::string print_CountryList();
	std::string print_ContinentList();
	int numberOfReinforcements();
	int total_number_of_armies_owned();
	void incrementBattlesWon();
	void setBattlesWon(int num);
	int getBattlesWon();
	int getNumberOfCards();
	std::string unbuild();

	Player(const Player &anotherPlayer);
	Player* build(std::string line, Map* m);

	
};

#endif