#pragma once
#include "Map.h"

using std::cout;


class MapTester
{
public:
	MapTester();
	~MapTester();
	void TestMapCreation();
	Map getMap() { return map; }

private:
	Map map;
};

