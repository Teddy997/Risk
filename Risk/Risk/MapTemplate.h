#pragma once

#include <string>
#include <vector>

using std::vector;
using std::string;

//This class is basically a box containing every but only information relative to a map
//This class is used when saving, loading or creating maps
class MapTemplate
{
public:
	MapTemplate();
	~MapTemplate();
	//Setters
	void Set_country_names(vector<string> new_country_names) {
		country_names = new_country_names;
	};
	void Set_continent_names(vector<string> new_continent_names) {
		continent_names = new_continent_names;
	};
	void Set_countries_adjacencies(vector < vector <int> > new_countries_adjacencies) {
		countries_adjacencies = new_countries_adjacencies;
	};
	void Set_continent_of_country(vector<int> new_continent_of_country) {
		continent_of_country = new_continent_of_country;
	};
	void Set_continent_bonus(vector<int> new_continent_bonus) {
		continent_bonus = new_continent_bonus;
	};
	void Set_countries_in_continent(vector< vector <int> > new_countries_in_continent) {
		countries_in_continent = new_countries_in_continent;
	}
	//getters
	vector<string> * Get_country_names() {
		return &country_names;
	};
	vector<string>* Get_continent_names() {
		return &continent_names;
	};
	vector < vector <int> >* Get_countries_adjacencies() {
		return &countries_adjacencies;
	};
	vector<int>* Get_continent_of_country() {
		return &continent_of_country;
	};
	vector<int>* Get_continent_bonus() {
		return &continent_bonus;
	};
	vector< vector <int> >* Get_countries_in_continent() {
		return &countries_in_continent;
	};

private:
	vector<string> country_names;
	vector<string> continent_names;
	vector < vector <int> > countries_adjacencies;		//First index = A country	Second index = its adjacencies
	vector<int> continent_of_country;
	vector<int> continent_bonus;
	vector< vector <int> > countries_in_continent;		//First index = A continent	Second index = the countries it contains
};

