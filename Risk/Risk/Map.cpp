#include "stdafx.h"
#include "Map.h"
#include <fstream>
#include <sstream>

Map::Map(MapTemplate mapTemplate)
{
	mapDirectory = mapTemplate.map_name;
	CreateContinents(mapTemplate.continent_names, mapTemplate.continent_bonus);
	CreateCountries(mapTemplate.country_names, mapTemplate.continent_of_country);
	AssignConnectedCountries(mapTemplate.countries_adjacencies);
	AssignContainedCountries(mapTemplate.continent_of_country);
}

Map::Map(string name)
{
	cout << "Trying to load map with name " << name << endl;
	mapDirectory = name;
	string continentFile = "Maps//" + name + "//continents.txt";
	string countriesFile = "Maps//" + name + "//countries.txt";
	vector<string> continentName;
	vector<int> continentID;
	vector<int> continentBonusValue;

	vector<string> countryName;
	vector<int> countryID;
	vector<int> containingContinentID;
	vector < vector <int> > connectedCountryID;

	ReadContinents(continentFile, continentName, continentID,continentBonusValue);
	CreateContinents(continentName, continentID, continentBonusValue);
	ReadCountries(countriesFile, countryName, countryID, containingContinentID, connectedCountryID);
	CreateCountries(countryName, containingContinentID);
	AssignConnectedCountries(connectedCountryID);
	AssignContainedCountries(containingContinentID);
}
Map::Map() {
	Map("default");
}
Map::~Map()
{
}

//void Map::CheckContinentBonus()
//{
//	//TODO: need to reset bonus first
//
//	Player* tempPlayer;
//	for(unsigned int i = 0; i < continents.size(); i++)
//	{
//		vector<Country*> tempCountries = continents[i].getContainedCountries();
//		tempPlayer = tempCountries[0]->get_owner();
//		bool deserveBonus = true;
//		for(unsigned int j = 1; j < tempCountries.size(); j++)
//		{
//			//TODO: make sure this comparison can work with these pointers
//			//I'm pretty sure this is crashing because there are no players assigned to any countries - Eric
//			if (tempCountries[j]->get_owner() != tempPlayer)
//			{
//				deserveBonus = false;
//				break;
//			}
//		}
//		if (deserveBonus)
//			tempPlayer->addBonus(continents[i].get_bonus());
//	}
//}

void Map::PrintAllCountryNames()
{
	for (unsigned int i = 0; i < nOfCountries; i++)
	{
		std::cout << countries[i]->get_country_name() << endl;
	}
}

void Map::PrintAllContinentNames()
{
	for(unsigned int i = 0; i < nOfContinents; i++)
	{
		std::cout << "--------------------------------------------------" << endl;
		std::cout << "\t\t" << continents[i].get_continent_name() << endl;
		std::cout << "////////////////////////////////" << endl;
		continents[i].PrintContainedCountries();
	}
}

int Map::test_map_components()
{
	int returnValue = 0;
	//TODO: using bit Flags for error code! -Cynthia

	if (countries.empty() || continents.empty())
	{
		returnValue = -1;
		if (countries.empty())
			std::cout << "There is no country in the map" << std::endl;
		if (continents.empty())
			std::cout << "There is no continent in the map" << std::endl;
	}
	else
	{
		////////////////REQ : Every country is in a continent, but only one///////////////////////////

		//for every countries
		for(unsigned int i = 0; i < countries.size(); i++)
		{
			Country* tempCountry = countries.at(i);
			Continent* tempContinent = tempCountry->get_containing_continent();
			if (tempContinent == NULL) {
				returnValue = -1;
				std::cout << tempCountry->get_country_name() << " doesn't have a containing continent" << std::endl;
			}
			for(unsigned int j = 0; j < continents.size(); j++)
			{
				//For all the other continents that contain countries
				if (&continents.at(j) != tempContinent && !continents.at(j).getContainedCountries().empty()) {
					for(unsigned int k = 0; k < continents.at(j).getContainedCountries().size(); k++)
					{
						//If another reference to the same country is found in another continent
						if (continents.at(j).getContainedCountries().at(k) == tempCountry) {
							returnValue = -1;
							std::cout << tempCountry->get_country_name() << " have been found more than 1 continent: " << continents.at(j).get_continent_name() << std::endl;
						}
					}
				}
			}
			////////////////REQ : Every country has at least 1 adjacency ///////////////////////////
			if (tempCountry->getConnectedCountries().empty())
			{
				returnValue = -1;
				std::cout << tempCountry->get_country_name() << " does not have any adjacency " << std::endl;
			}
		}
		////////////////REQ : Every continent has at least 1 country ///////////////////////////
		for(unsigned int i = 0; i < continents.size(); i++)
		{
			if (continents.at(i).getContainedCountries().empty())
			{
				returnValue = -1;
				std::cout << continents.at(i).get_continent_name() << " does not contain any country " << std::endl;
			}
		}
	}
	return returnValue;
}

////////////////////////Private Methods//////////////////////////

//Must be in the form:
//	String continent Name,int continentID
void Map::ReadContinents(string fileName, vector<string>& continentName, vector<int>& continentID, vector<int>& continentBonusValue)
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
		continentBonusValue.push_back(atoi(splittedLine[2].c_str()));
	}
	inputFile.close();
}

void Map::CreateContinents(vector<string>& continentName, vector<int>& continentID, vector<int>& continentBonusValue)
{
	for(unsigned int j = 0; j < continentName.size(); j++)
	{
		continents.push_back(Continent(continentName[j],continentID[j],continentBonusValue[j]));
	}
	set_nOfContinents(continents.size());
}

//Overloaded method
void Map::CreateContinents(vector<string>& continentName, vector<int>& continentBonusValue)
{
	for (unsigned int j = 0; j < continentName.size(); j++)
	{
		continents.push_back(Continent(continentName[j], j, continentBonusValue[j]));
	}
	set_nOfContinents(continents.size());
}

//Must be in the form:
//	String country Name,int countryID,int ContinentID,int connectedCountry1,int connectedCountry2, ...
void Map::ReadCountries(string fileName, vector<string>& countryName, vector<int>& countryID, vector<int>& containingContinentID,
						vector < vector <int> >& connectedCountryID)
{
	std::ifstream inputFile;
	inputFile.open(fileName);

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

		for(unsigned int j = 3; j < splittedLine.size(); j++)
		{
			connectedCountryID.at(i).push_back(atoi(splittedLine[j].c_str()));
		}
		i++;	//Keeps track of the first dimension for the 2dimensional vector
	}

	inputFile.close();
}

//Create the whole list  of countries
//NOTE: The continent list must be created before which is 
//		why the method is private
void Map::CreateCountries(vector<string>& countryName, vector<int>& containingContinentID)
{
	for(unsigned int j = 0; j < countryName.size(); j++)
	{
		countries.push_back(new Country(countryName[j], continents[containingContinentID[j]]));
	}
	set_nOfCountries(countries.size());
}

//Use only if countries are instantiated
void Map::AssignConnectedCountries(vector < vector <int> >& connectedCountryID)
{
	//Fetches a list of pointers to connected countries
	for(unsigned int j = 0; j < nOfCountries; j++)
	{
		vector<Country*> connected;
		for(unsigned int k = 0; k < connectedCountryID[j].size(); k++)
		{
			int index = connectedCountryID[j][k];
			connected.push_back(countries[index]);

		}
		countries[j]->setConnectedCountries(connected);
	}
}

//Use only if countries and continents are instantiated
void Map::AssignContainedCountries(vector<int>& containingContinentID)
{
	//For every country, add a reference in the row corresponding to 
	//the continent it is contained in
	vector < vector <Country*> > countriesContainedInContinent(nOfContinents, vector<Country*>());
	for (unsigned int j = 0; j < countries.size(); j++)
	{
		countriesContainedInContinent[containingContinentID[j]].push_back(countries[j]);
	}
	for (unsigned int j = 0; j < nOfContinents; j++)
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

int Map::nbOfCountries() {
	return nOfCountries;
}

vector<Country*> Map::getCountries() {
	/*vector<Country*> cs;
	for(unsigned int i = 0; i < countries.size(); ++i) {
		Country* t = &countries.at(i);
		cs.push_back(t);
	}*/
	return countries;

}

void Map::setupObservers() {
	MapObserver* mapObs = new MapObserver();
	for (int i = 0; i < countries.size(); i++) { 
		countries.at(i)->registerObserver(mapObs); 
	}
	cout << "Map observer initiated." << endl;
}