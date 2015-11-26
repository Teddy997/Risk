#pragma once
#include "IMapLoadableSavable.h"
#include "MapTemplate.h"

//Class used to save and load conquest maps
//using the ".map" extension

class ConquestMapLoaderSaver :
	public IMapLoadableSavable
{
public:
	ConquestMapLoaderSaver();
	~ConquestMapLoaderSaver();

	virtual void Save(MapTemplate mapTemplate);
	virtual MapTemplate Load(std::string mapName);
};

