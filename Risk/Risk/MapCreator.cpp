#include "MapCreator.h"

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
		Add_or_remove();
		cout << "Are you done?" << endl << "1: Yes, I want to save\t2: No, moar changes" << endl;
		if (mapTemplate.country_names.size() > 1) {
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
	//Select the saving format
	cout << "In which format would to save your map?\n1: .txt\t2: .map" << endl;
	int extension = InputProcedure::get_choice();
	Constants::MapExtension chosenMapExtension = Constants::MapExtension::TXT;	//Needed to be initialized
	if (extension == 1) {
		chosenMapExtension = Constants::MapExtension::TXT;
	}
	else if (extension == 2) {
		chosenMapExtension = Constants::MapExtension::CONQUEST;
	}

	mapTemplate.map_name = name;
	Save_map(chosenMapExtension);
}

void MapCreator::Save_map(Constants::MapExtension mapExtension)
{
	MapLoaderSaverAdapter mlsa;
	mlsa.Save(mapTemplate, mapExtension);
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
		if (mapTemplate.continent_names.empty()) {
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
		Add_new("continent", &mapTemplate.continent_names);
		Add_bonus();
		continent = mapTemplate.continent_names.size() - 1;	//The last added
		vector <int> newRow;
		mapTemplate.countries_in_continent.push_back(newRow);
	}
	else {
		continent = Choose_continent();
	}

	Add_new("country", &mapTemplate.country_names);
	vector<int> temp_adj = Choose_adjacencies();
	mapTemplate.countries_adjacencies.push_back(temp_adj);
	Update_other_adjacencies(temp_adj);
	mapTemplate.continent_of_country.push_back(continent);
}

void MapCreator::Add_or_remove()
{
	cout << "What would you like to do?" << endl << "0:	Add a country		1:	Remove a country" << endl;
	int choice = 3;
	do
	{
		choice = InputProcedure::get_choice();
	} while (choice < 0 || choice > 1);
	if (choice == 0)
	{
		New_country();
	}
	else
	{
		Remove_country();
	}
}

void MapCreator::Remove_country()
{
	cout << "REMOVE COUNTRY" << endl;

	if (mapTemplate.continent_names.size() <= 0)
	{
		cout << "You can't remove a country, there's NO country" << endl;
		Add_or_remove();
	}
	else
	{
		Helper::Display_formatted(mapTemplate.country_names);
		cout << "which country would you like to remove?" << endl;
		int countryIndex;
		do
		{
			countryIndex = InputProcedure::get_choice();
		} while (countryIndex < 0 && countryIndex > mapTemplate.continent_names.size() - 1);

	
		int continentIndex = mapTemplate.continent_of_country.at(countryIndex);
		int countriesinContinent = 0;
		//If it's the last country of a continent
		for (int i = 0; i < mapTemplate.continent_of_country.size(); i++)
		{
			if (mapTemplate.continent_of_country.at(i) == continentIndex)
				countriesinContinent++;
		}
		if (countriesinContinent <= 1)
		{
			Remove_country_from_template(countryIndex);
			Remove_continent_from_template(continentIndex);
		}
		else
		{
			Remove_country_from_template(countryIndex);
		}
		Add_or_remove();
	}
}


//Ewww Y__Y
void MapCreator::Remove_country_from_template(int country_index)
{
	//Simply removes the name, conaining continent and ajacencies of the country
	mapTemplate.country_names.erase(mapTemplate.country_names.begin() + country_index);
	mapTemplate.continent_of_country.erase(mapTemplate.continent_of_country.begin() + country_index);
	mapTemplate.countries_adjacencies.erase(mapTemplate.countries_adjacencies.begin() + country_index);

	//Has to go through all countries in continent to erase itself, and shift every other ID/index bigger than itself
	for (int i = 0; i < mapTemplate.countries_in_continent.size(); i++)
	{
		for (int j = 0; j < mapTemplate.countries_in_continent.at(i).size(); j++)
		{
			if (mapTemplate.countries_in_continent.at(i).at(j) == country_index)
			{
				mapTemplate.countries_in_continent.at(i).erase(mapTemplate.countries_in_continent.at(i).begin() + j);
				j--; //Since we removed an element, index have been shifted and we need need to reevaluate that index
				continue;
			}
			else if (mapTemplate.countries_in_continent.at(i).at(j) > country_index)
			{
				mapTemplate.countries_in_continent.at(i).at(j) -= 1;
			}
		}
	}

	//Has to go through all countries in countries_adjacencies to erase itself, and shift every other ID/index bigger than itself
	for (int i = 0; i < mapTemplate.countries_adjacencies.size(); i++)
	{
		for (int j = 0; j < mapTemplate.countries_adjacencies.at(i).size(); j++)
		{
			if (mapTemplate.countries_adjacencies.at(i).at(j) == country_index)
			{
				mapTemplate.countries_adjacencies.at(i).erase(mapTemplate.countries_adjacencies.at(i).begin() + j);
				j--; //Since we removed an element, index have been shifted and we need need to reevaluate that index
				continue;
			}
			else if (mapTemplate.countries_adjacencies.at(i).at(j) > country_index)
			{
				mapTemplate.countries_adjacencies.at(i).at(j) -= 1;
			}
		}
	}
}

void MapCreator::Remove_continent_from_template(int continent_index)
{
	//Simply removes the name, of the continent
	mapTemplate.continent_names.erase(mapTemplate.continent_names.begin() + continent_index);
	mapTemplate.continent_bonus.erase(mapTemplate.continent_bonus.begin() + continent_index);
	mapTemplate.countries_in_continent.erase(mapTemplate.countries_in_continent.begin() + continent_index);

	//Has to go through all countries in continent to erase itself, and shift every other ID/index bigger than itself
	for (int i = 0; i < mapTemplate.continent_of_country.size(); i++)
	{
		if (mapTemplate.continent_of_country.at(i) == continent_index)
		{
			//This should not happen, every country of a continent should be deleted before the continent
		}
		else if (mapTemplate.continent_of_country.at(i) > continent_index)
		{
			mapTemplate.continent_of_country.at(i) -= 1;
		}
	}
}

void MapCreator::Add_new(string item, vector<string>* destination)
{
	bool wrongName = true;
	string temp_name;

	while (wrongName)
	{
		temp_name = Ask_name(item);
		if (Helper::Search_for_duplicate(temp_name, *destination)) {
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

int MapCreator::Choose_continent()
{
	unsigned int chosen_one;
	Helper::Display_formatted(mapTemplate.continent_names);	//TODO: not sure about this needs verification
	do
	{
		cout << "please choose a continent" << endl;
		chosen_one = InputProcedure::get_choice();
	} while (chosen_one < 0 || chosen_one >= mapTemplate.continent_names.size());
	return chosen_one;
}

vector<int> MapCreator::Choose_adjacencies()
{
	bool go_on = true;
	bool wrong_number = false;
	int input;
	vector<int> chosen_adj;
	vector<string> countries_without_last(mapTemplate.country_names);	//TODO: not sure about this either, needs verification
	countries_without_last.pop_back();

	cout << "A country also needs adjacencies" << endl;
	
	if (mapTemplate.country_names.size() == 1) {
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
			else if (Helper::Search_for_duplicate(input, chosen_adj)) {
				cout << "You have already taken this one" << endl;
			}
			else {
				cout << mapTemplate.country_names.at(input) + " has been added as an adjacency!" << endl;
				chosen_adj.push_back(input);
				at_least_one++;
			}
		} while (go_on);
	}
	return chosen_adj;
}


void MapCreator::Update_other_adjacencies(vector<int> to_check)
{
	int current_country = (mapTemplate.country_names.size() - 1);
	if (!to_check.empty()) {
		for (unsigned int i = 0; i < to_check.size(); i++)
		{
			int temp_country_id = to_check.at(i);
			if (!Helper::Search_for_duplicate(current_country, mapTemplate.countries_adjacencies.at(temp_country_id)))
				//For every new adjacency of last added country, add this last country to their adjacencies
				mapTemplate.countries_adjacencies.at(to_check.at(i)).push_back(mapTemplate.country_names.size() - 1);
		}
	}
}

//Return true if it worked and false otherwise
bool MapCreator::Load_existing_map(string mapName)
{
	MapLoaderSaverAdapter mlsa;
	mapTemplate = mlsa.Load(mapName);
	//If the mapTemplate's name hasn't been initialized, it means it didn't work
	if (mapTemplate.map_name == "")
	{
		return false;
	}
	return true;
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
	mapTemplate.continent_bonus.push_back(bonus_value);
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
	Helper::DisplayMapDirectoryContents();
	cout << "Please type the name of the map you want" << endl;
	string name;
	bool valid = false;
	while (valid == false) {
		getline(cin, name);
		valid = Load_existing_map(name);
	}
}