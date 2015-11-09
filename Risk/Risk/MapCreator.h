#pragma once
#include <string>
#include <vector>

using std::vector;
using std::string;

class GameState;

class MapCreator
{
public:
	MapCreator();
	~MapCreator();

	//TODO These should probably be in somewhere accessible by the map or the map loader as well
	static const string country_file_convention;
	static const string continent_file_convention;
	static const string default_directory;
	static const string user_defined_directory;

	void Create_map();

private:
	enum MapFrame {
		FROM_SCRATCH = 0,
		FROM_DEFAULT,
		FROM_EXISTING
	};

	string old_name;
	string template_map_name;	//Map from which the user start adding countries
	vector<string> country_names;
	vector<string> continent_names;
	//First index = A country	Second index = its adjacencies
	vector < vector <int> > countries_adjacencies;
	vector<int> continent_of_country;
	vector<int> continent_bonus;
	//First index = A continent	Second index = the countries it contains
	vector< vector <int> > countries_in_continent;
	MapFrame mapFrame;


	////Private methods
	void Add_new(string item, vector<string>* destination);
	void New_country();
	string Ask_name(string target);
	int Choose_continent();
	vector<int> Choose_adjacencies();
	template <typename T1>
	int Search_for_duplicate(T1 item, vector<T1> list);
	void display_formatted(vector<string> to_display);
	void Update_other_adjacencies(vector<int> to_check);
	void Save_map(string name);
	void Load_existing_map(string mapName);
	void Add_bonus();
	void Split(const string& fullString, char cSplitter, vector<string>& SplitStrings);
	void Introduction();
	void displayMapDirectoryContents();
	void Choose_existing_map();
	void Move_cursor_y(int column);
};

