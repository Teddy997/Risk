#pragma once

#include <string>
#include <vector>

using std::vector;
using std::string;

//This class is basically a box containing every but only information relative to a map
//This class is used when saving, loading or creating maps
//It can be incomplete
class MapTemplate
{
public:
	string map_name;
	vector<string> country_names;
	vector<string> continent_names;
	vector < vector <int> > countries_adjacencies;		//First index = A country	Second index = its adjacencies
	vector<int> continent_of_country;
	vector<int> continent_bonus;
	vector< vector <int> > countries_in_continent;		//First index = A continent	Second index = the countries it contains
};

