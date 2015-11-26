#include "TextMapLoaderSaver.h"
#include"Helper.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::cin;
using std::getline;

const std::string TextMapLoaderSaver::country_file_convention = "countries.txt";
const std::string TextMapLoaderSaver::continent_file_convention = "continents.txt";

TextMapLoaderSaver::TextMapLoaderSaver()
{
}


TextMapLoaderSaver::~TextMapLoaderSaver()
{
}

void Save(MapTemplate mapTemplate) {

}
MapTemplate TextMapLoaderSaver::Load(std::string mapName)
{
	MapTemplate mapTemplate;
	//Local variables to stock value before setting them in mapTemplate
	vector<string> country_names;
	vector<string> continent_names;
	vector < vector <int> > countries_adjacencies;
	vector<int> continent_of_country;
	vector<int> continent_bonus;
	vector< vector <int> > countries_in_continent;

	std::ifstream input_country, input_continent;
	string country_file_path = "Maps\\" + mapName + "\\" + country_file_convention;
	string continent_file_path = "Maps\\" + mapName + "\\" + continent_file_convention;
	std::string   line;
	std::cout << "Loading " + mapName << std::endl;
	////////////////CONTINENT/////////////////
	input_continent.open(continent_file_path);
	while (std::getline(input_continent, line))
	{
		vector<string> splittedLine;
		Helper::Split(line, ',', splittedLine);

		continent_names.push_back(splittedLine[0]);
		continent_bonus.push_back(atoi(splittedLine[2].c_str()));
	}
	mapTemplate.Set_continent_names(continent_names);
	mapTemplate.Set_continent_bonus(continent_bonus);

	input_continent.close();

	////////////////COUNTRY/////////////////
	input_country.open(country_file_path);

	while (std::getline(input_country, line))
	{
		vector<string> splittedLine;
		Helper::Split(line, ',', splittedLine);

		country_names.push_back(splittedLine[0]);
		continent_of_country.push_back(atoi(splittedLine[2].c_str()));

		vector <int> newRow;
		for (unsigned int j = 3; j < splittedLine.size(); j++)
		{
			newRow.push_back(atoi(splittedLine[j].c_str()));
		}
		countries_adjacencies.push_back(newRow);
	}
	mapTemplate.Set_country_names(country_names);
	mapTemplate.Set_continent_of_country(continent_of_country);
	mapTemplate.Set_countries_adjacencies(countries_adjacencies);
	input_country.close();

	return mapTemplate;
}
