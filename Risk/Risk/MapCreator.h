#pragma once
#include <string>

class MapCreator
{
public:
	MapCreator();
	~MapCreator();
	static const std::string country_file_convention;
	static const std::string continent_file_convention;
	void Create_map();

private:
	std::string new_map_name;
	std::string template_map_name;	//Map from which the user start adding countries
};

