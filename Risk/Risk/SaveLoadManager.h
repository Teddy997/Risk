#pragma once
#include <cereal/archives/xml.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>

class GameState;

class SaveLoadManager
{
public:
	SaveLoadManager();
	~SaveLoadManager();
	void SaveGame();
};

