#pragma once
#include "Strategy.h"
class RandomStrategy : public Strategy
{
public:
	RandomStrategy();
	~RandomStrategy();

	void attack(Player* p2);
};

