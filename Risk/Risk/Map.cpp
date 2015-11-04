#include "stdafx.h"
#include "Map.h"
#include <fstream>
#include <sstream>

Map::Map()
{
	string continentFile = "continents.txt";
	string countriesFile = "countries.txt";
	vector<string> continentName;
	vector<int> continentID;

	vector<string> countryName;
	vector<int> countryID;
	vector<int> containingContinentID;
	vector < vector <int> > connectedCountryID;

	ReadContinents(continentFile, continentName, continentID);
	CreateContinents(continentName, continentID);
	ReadCountries(countriesFile, countryName, countryID, containingContinentID, connectedCountryID);
	CreateCountries(countryName);
	AssignConnectedCountries(connectedCountryID);
	AssignContainedCountries(containingContinentID);
}

Map::~Map()
{
}

////////////////////////Private Methods//////////////////////////

//Must be in the form:
//	String continent Name,int continentID
void Map::ReadContinents(string fileName, vector<string>& continentName, vector<int>& continentID)
{
	std::ifstream inputFile;
	inputFile.open(fileName);
	string   line;

	while (std::getline(inputFile, line))
	{
		vector<string> splittedLine;
		Split(line, ',', splittedLine);

		continentName.push_back(splittedLine[0]);
		continentID.push_back(atoi(splittedLine[1].c_str()));
	}
	inputFile.close();
}

void Map::CreateContinents(vector<string>& continentName, vector<int>& continentID)
{
	for (int j = 0; j < continentName.size(); j++)
	{
		continents.push_back(Continent(continentName[j],continentID[j]));
	}
	set_nOfContinents(continents.size());
}

//Must be in the form:
//	String country Name,int countryID,int ContinentID,int connectedCountry1,int connectedCountry2, ...
void Map::ReadCountries(string fileName, vector<string>& countryName, vector<int>& countryID, vector<int>& containingContinentID,
						vector < vector <int> >& connectedCountryID)
{
	std::ifstream inputFile;
	inputFile.open("countries.txt");

	std::string   line;
	int i = 0;
	while (std::getline(inputFile, line))
	{
		vector<string> splittedLine;
		Split(line, ',', splittedLine);

		countryName.push_back(splittedLine[0]);
		countryID.push_back(atoi(splittedLine[1].c_str()));
		containingContinentID.push_back(atoi(splittedLine[2].c_str()));

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
}

void Map::CreateCountries(vector<string>& countryName)
{
	for (int j = 0; j < countryName.size(); j++)
	{
		countries.push_back(Country(countryName[j]));
	}
	set_nOfCountries(countries.size());
}

//Use only if countries are instantiated
void Map::AssignConnectedCountries(vector < vector <int> >& connectedCountryID)
{
	//Fetches a list of pointers to connected countries
	for (int j = 0; j < nOfCountries; j++)
	{
		vector<Country*> connected;
		for (int k = 0; k < connectedCountryID[j].size(); k++)
		{
			//ID start at 1 while index start at 0
			int index = connectedCountryID[j][k] - 1;
			connected.push_back(&countries[index]);
		}
		countries[j].setConnectedCountries(connected);
	}
}

//Use only if countries and continents are instantiated
void Map::AssignContainedCountries(vector<int>& containingContinentID)
{
	//TODO: When we'll have user defined maps, make sure
	//the continents id fit with the number or continent
	//in the other file

	//For every country, add a reference in the row corresponding to 
	//the continent it is contained in
	vector < vector <Country*> > countriesContainedInContinent(nOfContinents, vector<Country*>());
	for (int j = 0; j < countries.size(); j++)
	{
		countriesContainedInContinent[containingContinentID[j]].push_back(&countries[j]);
	}
	for (int j = 0; j < nOfContinents; j++)
	{
		continents[j].setContainedCountries(countriesContainedInContinent[j]);
	}
}

void Map::Split(const string& fullString, char cSplitter, vector<string>& SplitStrings) {
	int i = 0;
	int j = fullString.find(cSplitter);

	while (j >= 0) {
		SplitStrings.push_back(fullString.substr(i, j - i));
		i = ++j;
		j = fullString.find(cSplitter, j);

		if (j < 0) {
			SplitStrings.push_back(fullString.substr(i, fullString.length()));
		}
	}
}
