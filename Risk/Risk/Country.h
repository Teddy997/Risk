#ifndef COUNTRY_H
#define COUNTRY_H

#include <iostream>
#include <string>
#include <cereal/archives/xml.hpp>

#include "Subject.h"

class Player;
class Country;

class Country : public Subject {
private:
	/*Member variables*/
	std::string country_name;
	std::string continent_name;
	Player* owner;
	bool is_owned;
	int number_of_armies;
	std::vector<Country*> connectedCountries;
	
	std::vector<Observer*> observers;

	void notifyObservers();

public:
	Country();
	Country(std::string name);
	~Country();
	std::string get_country_name();
	void set_continent_name(std::string c_name);
	std::string get_continent_name();
	void setConnectedCountries(std::vector<Country*> connected) { connectedCountries = connected; }
	std::vector<Country*> getConnectedCountries() { return connectedCountries; }
	
	void set_owned(bool value, Player& player);
	Player* get_owner();
	std::string get_owner_name();
	bool owned();
	
	void increment_armies(int amt);
	void decrement_armies(int amt);
	int get_number_of_armies();

	template<class Archive>
	void serialize(Archive & archive) {
		archive(
			CEREAL_NVP(country_name),
			CEREAL_NVP(is_owned));
	};

	void registerObserver(Observer* o);
	void unregisterObserver(Observer* o);
};

#endif