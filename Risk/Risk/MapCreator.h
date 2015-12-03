#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <direct.h>
#include "MapTemplate.h"
#include "Helper.h"
#include "Constants.h"
#include "InputProcedure.h"
#include "MapLoaderSaverAdapter.h"

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
	void Save_map(Constants::MapExtension mapExtension);
	bool Load_existing_map(string mapName);
	void Add_bonus();
	void Introduction();
	void Choose_existing_map();
	void Remove_country();
	void Remove_country_from_template(int country_index);
	void Remove_continent_from_template(int country_index);
	void Add_or_remove();
};

