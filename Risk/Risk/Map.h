#pragma once
#include <cereal/archives/xml.hpp>
#include <cereal/types/vector.hpp>
#include <vector>
#include "Country.h"
#include "Continent.h"

using std::vector;
using std::string;

class Map
{
public:
	// this class should contain the countries, generated in the constructor preferably
	// I(Radu) need 2 methods: one that returns the total number of countries and
	// one that returns me a random country that cannot be returned more than once
	Map();
	~Map();
	void set_nOfCountries(int numberOfCountries) { nOfCountries = numberOfCountries; }
	void set_nOfContinents(int numberOfContinents) { nOfContinents = numberOfContinents; }

	template<class Archive>
	void serialize(Archive & archive) {
		archive(
			CEREAL_NVP(countries));
	};

private:
	std::vector<Country> countries;
	std::vector<Continent> continents;
	int nOfCountries;
	int nOfContinents;

	//private methods
	void ReadContinents(string fileName, vector<string>& continentName, vector<int>& continentID);
	void CreateContinents(vector<string>& continentName, vector<int>& continentID);
	void ReadCountries(string fileName, vector<string>& countryName, vector<int>& countryID, vector<int>& containingContinentID,
	vector < vector <int> >& connectedCountryID);
	void CreateCountries(vector<string>& countryName);
	void AssignConnectedCountries(vector < vector <int> >& connectedCountryID);
	void AssignContainedCountries(vector<int>& containingContinentID);
	void Split(const string& fullString, char cSplitter, vector<string>& splitStrings);
};

