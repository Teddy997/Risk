#pragma once
#include <string>
using std::string;

class Constants
{
public:
	enum MapExtension {
		TXT,
		CONQUEST,
		INVALID
	};
	static const string maps_directory;
	static const string country_file_convention;
	static const string continent_file_convention;
	static const string conquest_file_extension;
};
