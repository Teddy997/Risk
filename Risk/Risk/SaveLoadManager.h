#pragma once
#include <string>

class GameState;

class SaveLoadManager
{
private:
	std::string file;
public:
	SaveLoadManager();
	~SaveLoadManager();
	void setFile(std::string filename) { file = filename; }
	void SaveGame(GameState& currentState);
	GameState* LoadGame(std::string filename);
};

