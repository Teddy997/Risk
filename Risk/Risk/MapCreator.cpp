#include "MapCreator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "tinydir.h"
#include <direct.h>

using std::cout;
using std::cin;
using std::endl;
using std::getline;


MapCreator::MapCreator()
{
}


MapCreator::~MapCreator()
{
}

const std::string MapCreator::country_file_convention = "countries.txt";
const std::string MapCreator::continent_file_convention = "continents.txt";
const std::string default_directory = "";
const std::string user_defined_directory = "";

void MapCreator::Create_map()
{
	Introduction();
	int changes_to_make = 0;
	string name;
	do{
		New_country();
		cout << "Are you done?" << endl << "1: Yes, I want to save\t2:No, moar countries" << endl;
		cin >> changes_to_make;
	} while (changes_to_make != 1);


	int dontOverwrite = 0;
	if (mapFrame == FROM_SCRATCH || mapFrame == FROM_DEFAULT) {
		name = Ask_name("Map");
		mkdir(("Maps\\" + name).c_str());
		//TODO: check if name taken
	}
	else {
		do
		{
			cout << "Do you want to overwrite your old map?" << endl << "1:yes\t2:no" << endl;
			cin >> dontOverwrite;
		} while (dontOverwrite != 1 && dontOverwrite != 2);

		if (dontOverwrite == 2) {
			name = Ask_name("Map");
			mkdir(("Maps\\" + name).c_str());
			//TODO: check if name taken
		}
		else {
			name = old_name;
		}
	}
	dontOverwrite--;
	Save_map(name);
}

void MapCreator::Save_map(string name)
{
	std::ofstream outputFileContinent;
	string continent_file = "Maps\\" + name + "\\" + continent_file_convention;

	outputFileContinent.open(continent_file, std::ofstream::out);

	for (int i = 0; i < continent_names.size(); i++) {
		outputFileContinent << continent_names.at(i) << "," << i << "," << continent_bonus.at(i) << endl;
	}

	outputFileContinent.close();

	////////////////Country/////////////////

	std::ofstream outputFileCountry;
	string country_file = continent_file = "Maps\\" + name + "\\" + country_file_convention;

	outputFileCountry.open(country_file, std::ofstream::out);	//Append

	for (int i = 0; i < country_names.size(); i++) {
		outputFileCountry << country_names.at(i) << "," << i << "," << continent_of_country.at(i);
		for (int j = 0; j < countries_adjacencies.at(i).size(); j++) {
			outputFileCountry << "," << countries_adjacencies.at(i).at(j);
		}
		outputFileCountry << endl;
	}
	outputFileContinent.close();
}

void MapCreator::New_country()
{
	int existing;
	bool wrongChoice = true;
	int continent;
	string name;

	cout << "NEW COUNTRY" << endl;

	while (wrongChoice) {
		cout << "A country need to be inside a continent: " << endl;
		if (continent_names.empty())
			cout << "1:New Continent" << endl;		//Can't choose existing if there is none
		else
			cout << "1:New Continent \t\t 2:Existing Continent" << endl;

		cin >> existing;
		if (existing == 2 || existing == 1) {
			wrongChoice = false;
		}
		else {
			cout << "wrong input" << endl;
		}
	}

	if (existing == 1) {
		Add_new("continent", &continent_names);
		Add_bonus();
		continent = continent_names.size() - 1;	//The last added
		vector <int> newRow;
		countries_in_continent.push_back(newRow);
	}
	else {
		continent = Choose_continent();
	}

	Add_new("country", &country_names);
	vector<int> temp_adj = Choose_adjacencies();

	countries_adjacencies.push_back(temp_adj);
	Update_other_adjacencies(temp_adj);
	//countries_in_continent.at(continent).push_back(country_names.size()-1);
	continent_of_country.push_back(continent);
}

void MapCreator::Add_new(string item, vector<string>* destination)
{
	bool wrongName = true;
	string temp_name;

	while (wrongName)
	{
		temp_name = Ask_name(item);
		if (Search_for_duplicate(temp_name, *destination)) {
			cout << "That name is already token! ";
		}
		else {
			wrongName = false;
		}
	}
	destination->push_back(temp_name);
}

string MapCreator::Ask_name(string target)
{
	//TODO: make this better
	string name;
	cout << "Please enter a name for your " << target << endl;
	cin.sync();
	getline(cin, name);
	//cin >> name;
	return name;
}

template <typename T1>
int MapCreator::Search_for_duplicate(T1 item, vector<T1> list)
{
	int return_value = 0;
	if (!list.empty())
	{
		for (int i = 0; i < list.size(); i++)
		{
			if (list.at(i) == item) {
				return_value = 1;
				break;
			}
		}
	}
	return return_value;
}

int MapCreator::Choose_continent()
{
	int chosen_one;
	display_formatted(continent_names);
	do
	{
		cout << "please choose a continent" << endl;
		cin >> chosen_one;
	} while (chosen_one < 0 || chosen_one >= continent_names.size());
	return chosen_one;
}

vector<int> MapCreator::Choose_adjacencies()
{
	bool go_on = true;
	bool wrong_number = false;
	int input;
	vector<int> chosen_adj;
	vector<string> countries_without_last(country_names);
	countries_without_last.pop_back();

	cout << "A country also need adjacencies" << endl;

	if (country_names.size() == 1) {
		cout << "Looks like this it your first country, you will have the chance to add adjacencies from your second country." << endl;
	}
	else {
		display_formatted(countries_without_last);
		do
		{
			cout << "please choose a country and press enter" << endl << "If you have no more ajacency to add, enter a negative number" << endl;
			cin >> input;
			if (input < 0) {
				go_on = false;
			}
			else if (input >= countries_without_last.size()) {
				cout << "Invalid choice" << endl;
			}
			else if (Search_for_duplicate(input, chosen_adj)) {
				cout << "You have already took this one" << endl;
			}
			else {
				chosen_adj.push_back(input);
			}
		} while (go_on);
	}
	return chosen_adj;
}

void MapCreator::display_formatted(vector<string> to_display)
{
	int n_of_columns = 4;
	int space_between_columns = 25;
	int size = to_display.size();
	int rows = (size / n_of_columns);
	int current_id;
	//to get the ceiling
	rows += (size % n_of_columns == 0) ? 0 : 1;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < n_of_columns; j++)
		{
			current_id = (i * n_of_columns) + j;
			if (current_id >= size)
				break;
			cout << current_id << ": " << to_display.at(current_id);
			Move_cursor_y(space_between_columns * (j + 1));
		}
		cout << endl; //at the end of each row
	}
}

void MapCreator::Update_other_adjacencies(vector<int> to_check)
{
	int current_country = (country_names.size() - 1);
	if (!to_check.empty()) {
		for (int i = 0; i < to_check.size(); i++)
		{
			int temp_country_id = to_check.at(i);
			if (!Search_for_duplicate(current_country, countries_adjacencies.at(temp_country_id)))
				//For every new adjacency of last added country, add this last country to their adjacencies
				countries_adjacencies.at(to_check.at(i)).push_back(country_names.size() - 1);
		}
	}
}

void MapCreator::Load_existing_map(string mapName)
{
	std::ifstream input_country, input_continent;
	string country_file_path = "Maps\\default\\" + country_file_convention;
	string continent_file_path = "Maps\\default\\" + continent_file_convention;
	std::string   line;

	////////////////CONTINENT/////////////////
	input_continent.open(continent_file_path);
	input_continent.bad();
	while (std::getline(input_continent, line))
	{
		vector<string> splittedLine;
		Split(line, ',', splittedLine);

		continent_names.push_back(splittedLine[0]);
		continent_bonus.push_back(atoi(splittedLine[2].c_str()));
	}
	input_continent.close();

	////////////////COUNTRY/////////////////
	input_country.open(country_file_path);

	while (std::getline(input_country, line))
	{
		vector<string> splittedLine;
		Split(line, ',', splittedLine);

		country_names.push_back(splittedLine[0]);
		continent_of_country.push_back(atoi(splittedLine[2].c_str()));

		vector <int> newRow;
		for (int j = 3; j < splittedLine.size(); j++)
		{
			newRow.push_back(atoi(splittedLine[j].c_str()));
		}
		countries_adjacencies.push_back(newRow);
	}
	input_country.close();
}

void MapCreator::Split(const string& fullString, char cSplitter, vector<string>& SplitStrings) {
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

void MapCreator::Add_bonus()
{
	bool wrong = true;
	int bonus_value;

	while (wrong)
	{
		cout << "Please enter a bonus for your continent" << endl;
		cin >> bonus_value;
		if (bonus_value >= 0 || bonus_value <= 100) {
			wrong = false;
		}
		else {
			cout << "Please enter a number between 0 and 100" << endl;
		}
	}
	continent_bonus.push_back(bonus_value);
}

void MapCreator::Introduction()
{
	int choice1;
	cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
	cout << "||||||||||||||||||||| MAP EDITOR |||||||||||||||||||||||||" << endl;
	cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
	do
	{
		cout << "Welcome to the map editor, please make your choice : " << endl
			<< "1: Create new map from scratch\t2: Create new map from default\t 3: Edit existing map" << endl;
		cin >> choice1;
	} while (choice1 < 1 || choice1 > 3);
	choice1--;

	mapFrame = (MapFrame)choice1;

	switch (mapFrame)
	{
	case FROM_SCRATCH:
		break;
	case FROM_DEFAULT:
		Load_existing_map("default");
		break;
	case FROM_EXISTING:
		Choose_existing_map();
		break;
	default:
		break;
	}
}

void MapCreator::Choose_existing_map()
{
	displayMapDirectoryContents();
	cout << "PLease type the name of the map you want" << endl;
	string name;
	cin.sync();
	getline(cin, name);
	Load_existing_map(name);
}

void MapCreator::displayMapDirectoryContents() {
	string display = "";
	tinydir_dir dir;
	tinydir_open(&dir, "Maps");

	while (dir.has_next)
	{
		tinydir_file file;
		tinydir_readfile(&dir, &file);
		string filename = file.name;
		if (filename.compare("Thumbs.db") == 0 || filename.compare(".") == 0 || filename.compare("..") == 0) {
			display += "";
		}
		else {
			if (file.is_dir && (filename.compare("default") != 0))
			{
				display += filename;
				display += "\n";
			}
			else {
				display += "";
			}
		}
		tinydir_next(&dir);
	}

	tinydir_close(&dir);
	if (display.length() == 0) {
		cout << "There are currently no user created maps!" << endl;
	}
	else {
		cout << display << endl;
	}
}

void MapCreator::Move_cursor_y(int column)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD coord;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	coord.X = column;
	coord.Y = csbi.dwCursorPosition.Y;
	SetConsoleCursorPosition(hConsole, coord);
}

//Ask load or from scratch
////load
//Display available maps
//Ask for wich map
//Either copy infos of map here OR make copy of the files and add at the end
//go to newMap

////new map
//xxxx   Ask for a name  <-- put at the end and ask if override existing or new save
//xxxx   Make sure the name is available

//Add country
////New continent
//make new continent
////choose continent
//display a continent list with id
//let user choose
//Choose name
//check if available
//add country
//create ID
//Ask for adjacencies
//display country with ID and good formatting (many collumns) minus current country
//Ask user to enter adjacencies
//validation
//add adjacencies
//Update adjacent countries by adding this

//Make new continent
//Ask for a name		<- should be private method
//check if available	<- should be private method
//add to the list
//create id + save it