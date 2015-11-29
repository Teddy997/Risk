#pragma once
#include <string>
#include "Strategy.h"
class RandomStrategy : public Strategy
{
public:
	RandomStrategy();
	~RandomStrategy();
	std::string const getStratName() { return "Random"; };

	void attack(Player* p1,Player* p2);
};

