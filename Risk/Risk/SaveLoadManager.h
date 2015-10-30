#pragma once
#include <cereal/archives/xml.hpp>

class SaveLoadManager
{
public:
	SaveLoadManager();
	~SaveLoadManager();
	void SaveGame();
};

