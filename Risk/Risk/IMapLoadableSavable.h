#pragma once
#include <string>

class MapTemplate;

class IMapLoadableSavable
{
public:
	virtual void Save(MapTemplate mapTemplate) = 0;
	virtual MapTemplate Load(std::string mapName) = 0;
};