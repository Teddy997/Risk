#pragma once
#include "Strategy.h"
class DefensiveStrategy : public Strategy
{
public:
	DefensiveStrategy();
	~DefensiveStrategy();

	void attack(Player* p1,Player* p2);
};

