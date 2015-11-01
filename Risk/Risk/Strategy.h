#pragma once
#include "Player.h"
#include <iostream>
using namespace std;
class Strategy
{
protected:

	Player* p;
public:
	Strategy();
	virtual ~Strategy();

	virtual void attack(Player* p2) = 0;

};

