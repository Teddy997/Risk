#pragma once
#include <string>
#include "Strategy.h"
class NoStrategy : public Strategy
{
//private:
	//std::string stratName;
public:
	NoStrategy();
	~NoStrategy();
	std::string const getStratName() { return "NoStrategy"; };

	void attack(Player* p1, Player* p2);
};

