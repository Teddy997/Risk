#pragma once
#include "IMapLoadableSavable.h"
#include "MapTemplate.h"

//This is an adapter class
//It is used to make a bridge between the original TextMapLoaderSaver (adaptee)
//and the newly created interface IMapLoadableSavable
class TextMapLoaderSaverAdapter :
	public IMapLoadableSavable
{
public:
	TextMapLoaderSaverAdapter();
	~TextMapLoaderSaverAdapter();

	virtual void Save(MapTemplate mapTemplate);
	virtual MapTemplate Load(std::string mapName);
};

