#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

#include "Observer.h"

class Observer;

class Subject {
public:
	virtual void registerObserver(Observer* o) = 0;
	virtual void unregisterObserver(Observer* o) = 0;
	virtual void notifyObservers() = 0;
};

#endif