#include "stdafx.h"
#include "Map.h"
#include <fstream>
#include <sstream>

Map::Map()
{
	createCountries();
	createContinents();
}
//String country Name, countryID,ContinentID,

Map::~Map()
{
}

void Map::createContinents()
{
	std::ifstream inputFile;
	inputFile.open("continents.txt");

	vector<string> continentName;
	vector<int> continentID;
	string   line;

	while (std::getline(inputFile, line))
	{
		vector<string> splittedLine;
		split(line, ',', splittedLine);

		continentName.push_back(splittedLine[0]);
		continentID.push_back(atoi(splittedLine[1].c_str()));
	}

	inputFile.close();

	for (int j = 0; j < continentName.size(); j++)
	{
		continents.push_back(Continent(continentName[j],continentID[j]));
	}
}

void Map::createCountries()
{
	std::ifstream inputFile;
	inputFile.open("countries.txt");

	vector<string> countryName;
	vector<int> countryID;
	vector<int> continentID;
	vector < vector <int> > connectedCountryID;	//2 dimensional vector

	std::string   line;
	int i = 0;
	while (std::getline(inputFile, line))
	{
		vector<string> splittedLine;
		split(line, ',', splittedLine);

		countryName.push_back(splittedLine[0]);
		countryID.push_back(atoi(splittedLine[1].c_str()));
		continentID.push_back(atoi(splittedLine[2].c_str()));

		//Need to add a new Row (1st dimension)
		//before assigning values in the second dimension
		//otherwise it causes an out of bound error
		vector <int> newRow;
		connectedCountryID.push_back(newRow);

		for (int j = 3; j < splittedLine.size(); j++)
		{
			connectedCountryID.at(i).push_back(atoi(splittedLine[j].c_str()));
		}
		i++;	//Keeps track of the first dimension for the 2dimensional vector
	}

	inputFile.close();

	for (int j = 0; j < countryName.size(); j++)
	{
		countries.push_back(Country(countryName[j]));
	}

	vector<Country*> connected;
	connected.push_back(&countries[connectedCountryID[0][1]]);










}

void Map::split(const string& fullString, char cSplitter, vector<string>& splitStrings) {
	int i = 0;
	int j = fullString.find(cSplitter);

	while (j >= 0) {
		splitStrings.push_back(fullString.substr(i, j - i));
		i = ++j;
		j = fullString.find(cSplitter, j);

		if (j < 0) {
			splitStrings.push_back(fullString.substr(i, fullString.length()));
		}
	}
}
