#pragma once
#include <iostream>
#include <string>
#include "Combat.h"
using namespace std;

class Player;


class Strategy
{
protected:
	//std::string stratName;
	//std::string const getStratName();
	void combat(Country* c1, Country* c2);
public:
	Strategy();
	//Strategy(std::string strat) { stratName = strat; }
	virtual ~Strategy();

	virtual void attack(Player* p1, Player* p2) = 0;

	
};

