#pragma once
#include "Strategy.h"
class AgressiveStrategy : public Strategy
{
public:
	AgressiveStrategy();
	~AgressiveStrategy();

	void attack(Player* p2);

};
