#ifndef MAPOBSERVERPATTERN_H
#define MAPOBSERVERPATTERN_H

#include "MapSubjectPattern.h"

class MapSubjectPattern;

class MapObserverPattern {
public:
	virtual void update(MapSubjectPattern* s) = 0;
};

#endif