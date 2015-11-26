#pragma once

#include "IMapLoadableSavable.h"
#include "MapTemplate.h"
#include "Constants.h"

//Original way of saving and loading a map
//Called Adaptee in the adapter design pattern
class TextMapLoaderSaver
{
public:
	TextMapLoaderSaver();
	~TextMapLoaderSaver();
	void Save(MapTemplate mapTemplate);
	MapTemplate Load(std::string mapName);

};

