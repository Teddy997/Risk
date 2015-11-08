#ifndef MAPOBSERVER_H
#define MAPOBSERVER_H

#include <vector>

#include "Observer.h"
#include "Country.h"
#include "Subject.h"

class MapObserver : public Observer {
private:
	//Map* map;
	//std::vector<Country> countries;
	/*
	Observer displays:
	country name
	continent name
	country owner
	number of armies
	adjacencies
	*/
	//void print(int i);
public:
	//MapObserver(Map m);
	void update(Subject* s);
};

#endif