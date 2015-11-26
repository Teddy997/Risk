#include "TextMapLoaderSaver.h"

using std::cin;
using std::getline;

TextMapLoaderSaver::TextMapLoaderSaver()
{
}

TextMapLoaderSaver::~TextMapLoaderSaver()
{
}

void TextMapLoaderSaver::Save(MapTemplate mapTemplate) {
	std::ofstream outputFileContinent;
	string continent_file = Constants::maps_directory + mapTemplate.map_name + "\\" + Constants::continent_file_convention;

	outputFileContinent.open(continent_file, std::ofstream::out);

	for (unsigned int i = 0; i < mapTemplate.continent_names.size(); i++) {
		outputFileContinent << mapTemplate.continent_names.at(i) << "," << i << "," << mapTemplate.continent_bonus.at(i) << std::endl;
	}

	outputFileContinent.close();

	////////////////Country/////////////////

	std::ofstream outputFileCountry;
	string country_file = continent_file = Constants::maps_directory + mapTemplate.map_name + "\\" + Constants::country_file_convention;

	outputFileCountry.open(country_file, std::ofstream::out);	//Append

	for (unsigned int i = 0; i < mapTemplate.country_names.size(); i++) {
		outputFileCountry << mapTemplate.country_names.at(i) << "," << i << "," << mapTemplate.continent_of_country.at(i);
		for (unsigned int j = 0; j < mapTemplate.countries_adjacencies.at(i).size(); j++) {
			outputFileCountry << "," << mapTemplate.countries_adjacencies.at(i).at(j);
		}
		outputFileCountry << std::endl;
	}
	outputFileContinent.close();
}

MapTemplate TextMapLoaderSaver::Load(std::string mapName)
{
	MapTemplate mapTemplate;
	mapTemplate.map_name = mapName;

	std::ifstream input_country, input_continent;
	string country_file_path = Constants::maps_directory + mapName + "\\" + Constants::country_file_convention;
	string continent_file_path = Constants::maps_directory + mapName + "\\" + Constants::continent_file_convention;
	std::string   line;
	std::cout << "Loading " + mapName << std::endl;
	////////////////CONTINENT/////////////////
	input_continent.open(continent_file_path);
	while (std::getline(input_continent, line))
	{
		vector<string> splittedLine;
		Helper::Split(line, ',', splittedLine);

		mapTemplate.continent_names.push_back(splittedLine[0]);
		mapTemplate.continent_bonus.push_back(atoi(splittedLine[2].c_str()));
	}

	input_continent.close();

	////////////////COUNTRY/////////////////
	input_country.open(country_file_path);

	while (std::getline(input_country, line))
	{
		vector<string> splittedLine;
		Helper::Split(line, ',', splittedLine);

		mapTemplate.country_names.push_back(splittedLine[0]);
		mapTemplate.continent_of_country.push_back(atoi(splittedLine[2].c_str()));

		vector <int> newRow;
		for (unsigned int j = 3; j < splittedLine.size(); j++)
		{
			newRow.push_back(atoi(splittedLine[j].c_str()));
		}
		mapTemplate.countries_adjacencies.push_back(newRow);
	}

	input_country.close();

	return mapTemplate;
}
