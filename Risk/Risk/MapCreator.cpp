#include "MapCreator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <direct.h>
#include "InputProcedure.h"

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

const std::string default_directory = "";
const std::string user_defined_directory = "";

void MapCreator::Create_map()
{
	Introduction();
	int changes_to_make = 0;
	string name;
	do{
		New_country();
		cout << "Are you done?" << endl << "1: Yes, I want to save\t2: No, moar countries" << endl;
		if (mapTemplate.Get_country_names()->size() > 1) {
			bool valid = false;
			while (valid == false) {
				changes_to_make = InputProcedure::get_choice();
				if (changes_to_make == 1 || changes_to_make == 2) { valid = true; }
				else { cout << "Not a valid input." << endl; }
			}
		}
		else {
			bool valid = false;
			while (valid == false) {
				changes_to_make = InputProcedure::get_choice();
				if (changes_to_make == 2) { valid = true; }
				else if (changes_to_make == 1) { cout << "You cannot save the map. Your country needs an adjacency!" << endl; }
				else { cout << "Not a valid input." << endl; }
			}
		}
	} while (changes_to_make != 1);


	int dontOverwrite = 0;
	if (mapFrame == FROM_SCRATCH || mapFrame == FROM_DEFAULT) {
		name = Ask_name("Map");
		mkdir(("Maps//" + name).c_str());
		//TODO: check if name taken
	}
	else {
		do
		{
			cout << "Do you want to overwrite your old map?" << endl << "1: yes\t2: no" << endl;
			dontOverwrite = InputProcedure::get_choice();
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

	for (unsigned int i = 0; i < continent_names.size(); i++) {
		outputFileContinent << continent_names.at(i) << "," << i << "," << continent_bonus.at(i) << endl;
	}

	outputFileContinent.close();

	////////////////Country/////////////////

	std::ofstream outputFileCountry;
	string country_file = continent_file = "Maps\\" + name + "\\" + country_file_convention;

	outputFileCountry.open(country_file, std::ofstream::out);	//Append

	for (unsigned int i = 0; i < country_names.size(); i++) {
		outputFileCountry << country_names.at(i) << "," << i << "," << continent_of_country.at(i);
		for (unsigned int j = 0; j < countries_adjacencies.at(i).size(); j++) {
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
		cout << "A country needs to be inside a continent: " << endl;
		if (mapTemplate.Get_continent_names()->empty()) {
			cout << "1:New Continent" << endl;		//Can't choose existing if there is none
			existing = InputProcedure::get_choice();
			if (existing == 1) {
				wrongChoice = false;
			}
			else {
				cout << "wrong input" << endl;
			}
		}
		else {
			cout << "1:New Continent \t\t 2:Existing Continent" << endl;
			existing = InputProcedure::get_choice();
			if (existing == 2 || existing == 1) {
				wrongChoice = false;
			}
			else {
				cout << "wrong input" << endl;
			}
		}
	}

	if (existing == 1) {
		Add_new("continent", mapTemplate.Get_continent_names());
		Add_bonus();
		continent = mapTemplate.Get_continent_names()->size() - 1;	//The last added
		vector <int> newRow;
		mapTemplate.Get_countries_in_continent()->push_back(newRow);
	}
	else {
		continent = Choose_continent();
	}

	Add_new("country", mapTemplate.Get_country_names());
	vector<int> temp_adj = Choose_adjacencies();
	mapTemplate.Get_countries_adjacencies()->push_back(temp_adj);
	Update_other_adjacencies(temp_adj);
	//countries_in_continent.at(continent).push_back(country_names.size()-1);
	mapTemplate.Get_continent_of_country.push_back(continent);
}

void MapCreator::Add_new(string item, vector<string>* destination)
{
	bool wrongName = true;
	string temp_name;

	while (wrongName)
	{
		temp_name = Ask_name(item);
		if (Search_for_duplicate(temp_name, *destination)) {
			cout << "That name is already taken! ";
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
	return name;
}

template <typename T1>
int MapCreator::Search_for_duplicate(T1 item, vector<T1> list)
{
	int return_value = 0;
	if (!list.empty())
	{
		for (unsigned int i = 0; i < list.size(); i++)
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
	unsigned int chosen_one;
	Helper::Display_formatted(*mapTemplate.Get_continent_names());	//TODO: not sure about this needs verification
	do
	{
		cout << "please choose a continent" << endl;
		chosen_one = InputProcedure::get_choice();
	} while (chosen_one < 0 || chosen_one >= mapTemplate.Get_continent_names()->size());
	return chosen_one;
}

vector<int> MapCreator::Choose_adjacencies()
{
	bool go_on = true;
	bool wrong_number = false;
	int input;
	vector<int> chosen_adj;
	vector<string> countries_without_last(*mapTemplate.Get_country_names());	//TODO: not sure about this either, needs verification
	countries_without_last.pop_back();

	cout << "A country also needs adjacencies" << endl;
	
	if (mapTemplate.Get_country_names()->size() == 1) {
		cout << "Looks like this it your first country, you will have the chance to add adjacencies from your second country." << endl;
		//New_country();
	}
	else {
		int at_least_one = 0;
		Helper::Display_formatted(countries_without_last);
		do
		{
			cout << "please choose a country and press enter" << endl << "If you have no more ajacencies to add, enter a negative number" << endl;
			input = InputProcedure::get_choice();
			if (input < 0 && at_least_one == 1) {
				go_on = false;
			}
			else if (input < 0 && at_least_one == 0) {
				cout << "You must add at least one adjacency before moving on!" << endl;
			}
			else if (input >= countries_without_last.size()) {
				cout << "Invalid choice" << endl;
			}
			else if (Search_for_duplicate(input, chosen_adj)) {
				cout << "You have already taken this one" << endl;
			}
			else {
				cout << mapTemplate.Get_country_names()->at(input) + " has been added as an adjacency!" << endl;
				chosen_adj.push_back(input);
				at_least_one++;
			}
		} while (go_on);
	}
	return chosen_adj;
}


void MapCreator::Update_other_adjacencies(vector<int> to_check)
{
	int current_country = (country_names.size() - 1);
	if (!to_check.empty()) {
		for (unsigned int i = 0; i < to_check.size(); i++)
		{
			int temp_country_id = to_check.at(i);
			if (!Search_for_duplicate(current_country, countries_adjacencies.at(temp_country_id)))
				//For every new adjacency of last added country, add this last country to their adjacencies
				countries_adjacencies.at(to_check.at(i)).push_back(country_names.size() - 1);
		}
	}
}

//TODO
void MapCreator::Load_existing_map(string mapName)
{
	old_name = mapName;
	std::ifstream input_country, input_continent;
	string country_file_path = "Maps\\" + mapName + "\\" + country_file_convention;
	string continent_file_path = "Maps\\" + mapName + "\\" + continent_file_convention;

	//1. Search file inside location with mapName
	//2. check extension
	//3. if .txt ...  if .map ...

	//load should take the mapSave directory in parameters

}

void MapCreator::Add_bonus()
{
	bool wrong = true;
	int bonus_value;

	while (wrong)
	{
		cout << "Please enter a bonus for your continent" << endl;
		bool valid = false;
		while (valid == false) {
			bonus_value = InputProcedure::get_choice();
			if (bonus_value >= 0 && bonus_value <= 100) {
				wrong = false;
				valid = true;
			}
			else {
				cout << "Please enter a number between 0 and 100" << endl;
			}
		}
	}
	mapTemplate.Get_continent_bonus()->push_back(bonus_value);
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
		choice1 = InputProcedure::get_choice();
		if (choice1 < 1 || choice1 > 3) { cout << "Not a valid input." << endl; }
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
	cout << "Please type the name of the map you want" << endl;
	string name;
	bool valid = false;
	while (valid == false) {
		getline(cin, name);
		//Checking whether the map chosen is correct by seeing if countries opens
		string dirname = "Maps//" + name + "//countries.txt";
		std::fstream filestr;
		//If it does open, then the path is valid, and we can choose this map
		filestr.open(dirname);
		if (filestr.is_open()) {
			filestr.close();
			valid = true;
		}
		else { cout << "This map doesn't exist!" << endl; }
	}
	Load_existing_map(name);
}
