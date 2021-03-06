#pragma once

#include "MapTemplate.h"
#include "Constants.h"
#include"Helper.h"
#include <iostream>
#include <fstream>
#include <sstream>

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

