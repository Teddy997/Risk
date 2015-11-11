#include "stdafx.h"
#include "SaveLoadManager.h"
#include <fstream>
#include "GameState.h"

SaveLoadManager::SaveLoadManager()
{
}


SaveLoadManager::~SaveLoadManager()
{
}

void SaveLoadManager::SaveGame()
{
	std::srand(unsigned(std::time(0)));
	std::ofstream outputFile("gameSave.xml");
	cereal::XMLOutputArchive archive(outputFile);
	int hello = 5;
	char test = 's';
	int random = (rand() % 100) + 1; //for some reason it serializes only on changes, this is a work around
	GameState g("Jessie"); //testing
	g.addPlayer("Gus"); //testing
	string s = "Default_Map"; //testing
	g.setMap(s); //testing
	archive(CEREAL_NVP(random), CEREAL_NVP(g)); 

	
	//archive(hello, cereal::make_nvp("This is a char", test));
}