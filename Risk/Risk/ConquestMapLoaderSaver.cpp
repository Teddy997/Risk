#include "ConquestMapLoaderSaver.h"


ConquestMapLoaderSaver::ConquestMapLoaderSaver()
{
}


ConquestMapLoaderSaver::~ConquestMapLoaderSaver()
{
}

void ConquestMapLoaderSaver::Save(MapTemplate mapTemplate)
{
	std::ofstream outputFile;
	string file_path = Constants::maps_directory + mapTemplate.map_name + "\\" + mapTemplate.map_name + Constants::conquest_file_extension;

	outputFile.open(file_path, std::ofstream::out);

	outputFile << "[Continents]" << std::endl;

	for (unsigned int i = 0; i < mapTemplate.continent_names.size(); i++) {
		outputFile << mapTemplate.continent_names.at(i) << "=" << mapTemplate.continent_bonus.at(i) << std::endl;
	}

	outputFile << std::endl;

	outputFile << "[Territories]" << std::endl;

	for (unsigned int i = 0; i < mapTemplate.country_names.size(); i++) {
		outputFile << mapTemplate.country_names.at(i) << ",000,000," << mapTemplate.continent_names.at(mapTemplate.continent_of_country.at(i));
		for (unsigned int j = 0; j < mapTemplate.countries_adjacencies.at(i).size(); j++) {
			outputFile << "," << mapTemplate.country_names.at(mapTemplate.countries_adjacencies.at(i).at(j));
		}
	outputFile << std::endl;
	}
	outputFile.close();
}

MapTemplate ConquestMapLoaderSaver::Load(std::string mapName)
{
	MapTemplate mapTemplate;
	mapTemplate.map_name = mapName;

	std::fstream input_file;
	string file_path = Constants::maps_directory + mapName + "\\" + mapName + Constants::conquest_file_extension;
	std::string   line;
	std::string   contient_indicator = "[Continents]";
	std::string   country_indicator = "[Territories]";
	vector< vector <std::string> > connected_countries_names;
	std::cout << "Loading " + mapName << std::endl;
	input_file.open(file_path);
	
	bool test = input_file.is_open();

	bool readContinents = false;
	bool readCountries = false;

	while (std::getline(input_file, line))
	{
		//Check if line is empty
		if (line.empty())
			continue;

		//Check if the line starts with the continent indicator
		if (!line.compare(0, contient_indicator.size(), contient_indicator))
		{
			readContinents = true;
			continue;
		}

		//Check if the line starts with the country indicator
		if (!line.compare(0, country_indicator.size(), country_indicator))
		{
			readContinents = false;		//Stop readinf continents
			readCountries = true;		//and start reading countries
			continue;
		}

		if (readContinents)
		{
			vector<string> splittedLine;
			Helper::Split(line, '=', splittedLine);
			mapTemplate.continent_names.push_back(splittedLine[0]);
			mapTemplate.continent_bonus.push_back(atoi(splittedLine[1].c_str()));
		}

		if (readCountries)
		{
			vector<string> splittedLine;
			Helper::Split(line, ',', splittedLine);

			mapTemplate.country_names.push_back(splittedLine[0]);
			splittedLine[3].c_str();

			//TODO check is pos is from 0 or 1
			//Find the index of the continent containing the country
			int pos = find(mapTemplate.continent_names.begin(), mapTemplate.continent_names.end(), splittedLine[3].c_str()) - mapTemplate.continent_names.begin();
			mapTemplate.continent_of_country.push_back(pos);

			//Put the connected countries in a temporary vector
			vector <string> newRowStr;
			for (unsigned int j = 4; j < splittedLine.size(); j++)
			{
				newRowStr.push_back(splittedLine[j].c_str());
			}
			connected_countries_names.push_back(newRowStr);

			//Prepare the 2D agjacencies vector
			vector <int> newRowInt;
			mapTemplate.countries_adjacencies.push_back(newRowInt);
		}
	}
	for (int i = 0; i < connected_countries_names.size(); i++)
	{
		for (int j = 0; j < connected_countries_names.at(i).size(); j++)
		{
			//Find the index of the country
			int pos = find(mapTemplate.country_names.begin(), mapTemplate.country_names.end(),
				connected_countries_names.at(i).at(j)) - mapTemplate.country_names.begin();
			//Push the index in mapTemplate
			mapTemplate.countries_adjacencies.at(i).push_back(pos);
		}
	}
	input_file.close();

	return mapTemplate;
}