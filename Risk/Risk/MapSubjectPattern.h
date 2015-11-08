#ifndef MAPSUBJECTPATTERN_H
#define MAPSUBJECTPATTERN_H

#include <vector>

#include "MapObserverPattern.h"

class MapObserverPattern;

class MapSubjectPattern {
public:
	virtual void registerObserver(MapObserverPattern* o) = 0;
	virtual void unregisterObserver(MapObserverPattern* o) = 0;
	virtual void notifyObservers() = 0;
};

#endif