#ifndef OBSERVER_H
#define OBSERVER_H

#include "Subject.h"

class Subject;

class Observer {
public:
	virtual void update(Subject* s) = 0;
};

#endif