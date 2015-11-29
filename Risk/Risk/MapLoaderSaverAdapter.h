#pragma once
#include "MapTemplate.h"
#include "TextMapLoaderSaver.h"
#include "ConquestMapLoaderSaver.h"
#include "Constants.h"

class MapLoaderSaverAdapter
{
public:
	MapLoaderSaverAdapter();
	~MapLoaderSaverAdapter();
	void Save(MapTemplate mapTemplate, Constants::MapExtension mapExtension);
	MapTemplate Load(std::string mapName);
};

