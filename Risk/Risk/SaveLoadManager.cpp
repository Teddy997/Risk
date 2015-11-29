#include "stdafx.h"
#include "SaveLoadManager.h"
#include <fstream>
#include "GameState.h"
#include "Player.h"
#include <string>
#include <iostream>
#include <vector>

SaveLoadManager::SaveLoadManager()
{
}


SaveLoadManager::~SaveLoadManager()
{
}

void SaveLoadManager::SaveGame(GameState& currentState)
{
	/*
	map
	numPlayers
	player
	AIPlayers
	currentPlayer
	currentPhase
	*/
	
	std::ofstream saveOut;
	saveOut.open(file);
	saveOut << currentState.unbuild();
	saveOut.close();

}

GameState* SaveLoadManager::LoadGame(std::string filename) {
	std::string file_contents;
	std::string line;
	std::ifstream load("Saves//" + filename + ".txt");
	if (load.is_open()) {
		while (getline(load, line)) {
			file_contents += line + "\n";
		}
		load.close();
	}
	GameState* gs = new GameState();
	GameState* gs2 = (gs->build(file_contents));
	return gs2;	
}