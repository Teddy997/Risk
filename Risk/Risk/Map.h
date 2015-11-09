#pragma once
#include <cereal/archives/xml.hpp>
#include <cereal/types/vector.hpp>
#include <vector>
#include "Country.h"
#include "Continent.h"
#include "Subject.h"
#include "Observer.h"

using std::vector;
using std::string;

class Map
{
public:

	Map();
	~Map();

	vector<Country*> getAllCountries() { return countries; }

	void set_nOfCountries(int numberOfCountries) { nOfCountries = numberOfCountries; }
	void set_nOfContinents(int numberOfContinents) { nOfContinents = numberOfContinents; }

	void PrintAllCountryNames();
	void PrintAllContinentNames();
	void CheckContinentBonus();
	int test_map_components();

	template<class Archive>
	void serialize(Archive & archive) {
		archive(
			CEREAL_NVP(countries));
	};
	int nbOfCountries();
	std::vector<Country*> getCountries();
private:
	std::vector<Country*> countries;
	std::vector<Continent> continents;
	int nOfCountries;
	int nOfContinents;

	//private methods
	void ReadContinents(string fileName, vector<string>& continentName, vector<int>& continentID, vector<int>& continentBonusValue);
	void CreateContinents(vector<string>& continentName, vector<int>& continentID, vector<int>& continentBonusValue);
	void ReadCountries(string fileName, vector<string>& countryName, vector<int>& countryID, vector<int>& containingContinentID,
	vector < vector <int> >& connectedCountryID);
	void CreateCountries(vector<string>& countryName, vector<int>& containingContinentID);
	void AssignConnectedCountries(vector < vector <int> >& connectedCountryID);
	void AssignContainedCountries(vector<int>& containingContinentID);
	void Split(const string& fullString, char cSplitter, vector<string>& splitStrings);
};

