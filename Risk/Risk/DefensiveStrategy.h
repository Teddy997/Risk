#pragma once
#include <string>
#include "Strategy.h"
class DefensiveStrategy : public Strategy
{
//private:
	//std::string stratName;
public:
	DefensiveStrategy();
	~DefensiveStrategy();
	std::string const getStratName() { return "Defensive"; };

	void attack(Player* p1,Player* p2);
};

