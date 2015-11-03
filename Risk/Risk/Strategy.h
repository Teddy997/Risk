#pragma once
#include <iostream>
using namespace std;

class Player;

class Strategy
{
protected:
	Player* p;
public:
	Strategy();
	virtual ~Strategy();

	virtual void attack(Player* p2) = 0;

};

