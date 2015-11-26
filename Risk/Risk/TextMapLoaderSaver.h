#pragma once

#include "IMapLoadableSavable.h"
#include "MapTemplate.h"

//Original way of saving and loading a map
//Called Adaptee in the adapter design pattern
class TextMapLoaderSaver
{
public:
	TextMapLoaderSaver();
	~TextMapLoaderSaver();
	void Save(MapTemplate mapTemplate);
	MapTemplate Load(std::string mapName);

	static const string country_file_convention;
	static const string continent_file_convention;

private:

};

