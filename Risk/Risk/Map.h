#pragma once
#include <cereal/archives/xml.hpp>
#include <cereal/types/vector.hpp>
#include <vector>
#include "Country.h"

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
	template<class Archive>
	void serialize(Archive & archive) {
		archive(
			CEREAL_NVP(countries));
	};

private:
	std::vector<Country> countries;

	//private methods
	void createCountries();
	void split(const string& fullString, char cSplitter, vector<string>& splitStrings);
};

