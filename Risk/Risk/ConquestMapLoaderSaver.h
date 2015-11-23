#pragma once
#include "IMapSavableLoadable.h"
#include "MapTemplate.h"

//Class used to save and load conquest maps
//using the ".map" extension

class ConquestMapLoaderSaver :
	public IMapSavableLoadable
{
public:
	ConquestMapLoaderSaver();
	~ConquestMapLoaderSaver();

	virtual void Save(MapTemplate mapTemplate);
	virtual MapTemplate Load(std::string mapName);
};

