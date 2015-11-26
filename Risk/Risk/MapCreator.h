#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <direct.h>
#include "MapTemplate.h"
#include "Helper.h"
#include "TextMapLoaderSaver.h"
#include "ConquestMapLoaderSaver.h"
#include "Constants.h"
#include "InputProcedure.h"

using std::vector;
using std::string;

class GameState;

class MapCreator
{
public:
	MapCreator();
	~MapCreator();

	void Create_map();

private:
	enum MapFrame {
		FROM_SCRATCH = 0,
		FROM_DEFAULT,
		FROM_EXISTING
	};

	enum MapExtension {
		TXT = 0,
		CONQUEST
	};

	MapTemplate mapTemplate;
	string old_name;
	string template_map_name;	//Map from which the user start adding countries
	MapFrame mapFrame;


	////Private methods
	void Add_new(string item, vector<string>* destination);
	void New_country();
	string Ask_name(string target);
	int Choose_continent();
	vector<int> Choose_adjacencies();
	void Update_other_adjacencies(vector<int> to_check);
	void Save_map(MapExtension mapExtension);
	void Load_existing_map(string mapName, MapExtension mapExtension);
	void Add_bonus();
	void Introduction();
	void Choose_existing_map();
};

