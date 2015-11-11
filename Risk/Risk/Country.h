#ifndef COUNTRY_H
#define COUNTRY_H

#include <iostream>
#include <string>
#include <cereal/archives/xml.hpp>
//#include "Continent.h"

#include "MapSubjectPattern.h"
#include "subject.h"

class Player;
class Continent;
class Country;

class Country : public MapSubjectPattern,public Subject {
private:
	/*Member variables*/
	std::string country_name;
	std::string continent_name;
	Continent* containing_continent;
	Player* owner;
	bool is_owned;
	int number_of_armies;
	std::vector<Country*> connectedCountries;
	
	std::vector<MapObserverPattern*> observers;

	void notifyObservers();

public:
	Country();
	Country(std::string name, Continent& continent) : Country(name) { containing_continent = &continent; };
	Country(std::string name);
	~Country();
	std::string get_country_name();
	Player* getOwner() { return owner; }
	void set_continent_name(std::string c_name);
	std::string get_continent_name();
	void setConnectedCountries(std::vector<Country*> connected) { connectedCountries = connected; }
	std::vector<Country*> getConnectedCountries() { return connectedCountries; }
	Continent* get_containing_continent() { return containing_continent; };
	
	void set_owned(bool value, Player& player);
	Player* get_owner();
	std::string get_owner_name();
	bool owned();
	
	void increment_armies(int amt);
	void decrement_armies(int amt);
	int get_number_of_armies();
	void printConnectedCountries();
	template<class Archive>
	void serialize(Archive & archive) {
		archive(
			CEREAL_NVP(country_name),
			CEREAL_NVP(is_owned));
	}

	void registerObserver(MapObserverPattern* o);
	void unregisterObserver(MapObserverPattern* o);
};

#endif