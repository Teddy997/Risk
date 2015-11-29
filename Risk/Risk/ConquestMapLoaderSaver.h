#pragma once
#include "MapTemplate.h"
#include "Constants.h"
#include"Helper.h"
#include <iostream>
#include <fstream>
#include <sstream>

//Class used to save and load conquest maps
//using the ".map" extension

class ConquestMapLoaderSaver
{
public:
	ConquestMapLoaderSaver();
	~ConquestMapLoaderSaver();

	void Save(MapTemplate mapTemplate);
	MapTemplate Load(std::string mapName);
};

