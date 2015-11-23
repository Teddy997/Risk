#pragma once
#include <string>

class MapTemplate;

class IMapSavableLoadable
{
public:
	virtual void Save(MapTemplate mapTemplate) = 0;
	virtual MapTemplate Load(std::string mapName) = 0;
};