#include "MapTester.h"


MapTester::MapTester()
{
}


MapTester::~MapTester()
{
}

void MapTester::TestMapCreation()
{
	int wait;
	map.PrintAllCountryNames();
	map.PrintAllContinentNames();
	std::cin >> wait;
}