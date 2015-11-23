#pragma once
#include <string>
#include "Strategy.h"
class AgressiveStrategy : public Strategy
{
//private:
	//std::string stratName;
public:
	AgressiveStrategy();
	~AgressiveStrategy();
	//std::string const getStratName() { return stratName; };

	void attack(Player* p1, Player* p2);

};

