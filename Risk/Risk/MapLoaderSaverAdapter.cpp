#include "MapLoaderSaverAdapter.h"


MapLoaderSaverAdapter::MapLoaderSaverAdapter()
{
}


MapLoaderSaverAdapter::~MapLoaderSaverAdapter()
{
}

void MapLoaderSaverAdapter::Save(MapTemplate mapTemplate, Constants::MapExtension mapExtension)
{
	if (mapExtension == Constants::MapExtension::TXT)
	{
		TextMapLoaderSaver tmls;
		tmls.Save(mapTemplate);
	}
	else if (mapExtension == Constants::MapExtension::CONQUEST)
	{
		ConquestMapLoaderSaver cmls;
		cmls.Save(mapTemplate);
	}
}

MapTemplate MapLoaderSaverAdapter::Load(std::string mapName)
{
	MapTemplate mapTemplate;
	string dirname_txt = Constants::maps_directory + mapName + "\\countries.txt";
	string dirname_conquest = Constants::maps_directory + mapName + "\\" + mapName + ".map";
	std::fstream filestr;
	//If it does open the .txt, then the path is valid, and we can choose this map
	filestr.open(dirname_txt);
	if (filestr.is_open()) {
		filestr.close();
		TextMapLoaderSaver tmls;
		mapTemplate = tmls.Load(mapName);
	}
	//Else, try to open as a conquest map
	else {
		filestr.open(dirname_conquest);
		if (filestr.is_open()) {
			filestr.close();
			ConquestMapLoaderSaver cmls;
			mapTemplate = cmls.Load(mapName);
		}
		else { std::cout << "Unable to open map : " << mapName << std::endl; }
	}
	return mapTemplate;
}