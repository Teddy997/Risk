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
	
	std::ofstream outputFile("gameSave.xml");
	cereal::XMLOutputArchive archive(outputFile);
	int hello = 5;
	char test = 's';

	//GameState gameState;
	//archive(CEREAL_NVP(gameState), hello, test); 
	
	//archive(hello, cereal::make_nvp("This is a char", test));
}