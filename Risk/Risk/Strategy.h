#pragma once
#include <iostream>
#include "Combat.h"
using namespace std;

class Player;


class Strategy
{

public:
	Strategy();
	virtual ~Strategy();

	virtual void attack(Player* p1, Player* p2) = 0;

};

