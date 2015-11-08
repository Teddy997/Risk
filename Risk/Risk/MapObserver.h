#ifndef MAPOBSERVER_H
#define MAPOBSERVER_H

#include <vector>

#include "MapObserverPattern.h"
#include "Country.h"
#include "MapSubjectPattern.h"

class MapObserver : public MapObserverPattern {
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
	void update(MapSubjectPattern* s);
};

#endif