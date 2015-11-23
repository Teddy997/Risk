#pragma once
#include "IMapSavableLoadable.h"
#include "MapTemplate.h"

//This is an adapter class
//It is used to make a bridge between the original TextMapLoaderSaver (adaptee)
//and the newly created interface IMapSavableLoadable
class TextMapLoaderSaverAdapter :
	public IMapSavableLoadable
{
public:
	TextMapLoaderSaverAdapter();
	~TextMapLoaderSaverAdapter();

	virtual void Save(MapTemplate mapTemplate);
	virtual MapTemplate Load(std::string mapName);
};

