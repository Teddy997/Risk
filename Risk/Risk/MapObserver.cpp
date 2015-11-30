#include "MapObserver.h"

//MapObserver::MapObserver(Map m) {
//	map = &m;
//	countries = map->getAllCountries();
//}

void MapObserver::update(MapSubjectPattern* s) {
	Country* c = dynamic_cast<Country*>(s);
	std::cout << "COUNTRY VALUES HAVE BEEN UPDATED" << std::endl;
	std::cout << "COUNTRY: " + c->get_country_name() << std::endl;
	std::cout << "CONTINENT: " + c->get_continent_name() << std::endl;
	std::cout << "OWNER: " + c->get_owner_name() << std::endl;
	std::cout << "ARMIES: " << c->get_number_of_armies() << std::endl;
	
	std::vector<Country*> adjacencies = c->getConnectedCountries();
	std::cout << "ADJACENCIES: ";
	for (int i = 0; i < adjacencies.size(); i++) {
		if (i != adjacencies.size() - 1) {
			std::cout << adjacencies.at(i)->get_country_name() + ", ";
		}
		else { std::cout << adjacencies.at(i)->get_country_name() << std::endl; }
	}
	std::cout << std::endl;
	/*countries = map->getAllCountries();
	int num_of_countries = countries.size();
	std::string na = "North America";
	std::string sa = "South America";
	std::string eu = "Europe";
	std::string af = "Africa";
	std::string as = "Asia";
	std::string au = "Australia";
	std::cout << "***************************** MAP OBSERVER *****************************" << std::endl;
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 0:
			std::cout << "\n***************************** NORTH AMERICA *****************************"; break;
		case 1:
			std::cout << "\n***************************** SOUTH AMERICA *****************************"; break;
		case 2:
			std::cout << "\n***************************** EUROPE *****************************"; break;
		case 3:
			std::cout << "\n***************************** AFRICA *****************************"; break;
		case 4:
			std::cout << "\n***************************** ASIA *****************************"; break;
		default: 
			std::cout << "\n***************************** AUSTRALIA *****************************"; break;
		}
		for (int j = 0; j < num_of_countries; j++) {
			if (countries.at(j).get_continent_name().compare(na) == 0 && i == 0) {
				print(j);
			}
			if (countries.at(j).get_continent_name().compare(sa) == 0 && i == 1) {
				print(j);
			}
			if (countries.at(j).get_continent_name().compare(eu) == 0 && i == 2) {
				print(j);
			}
			if (countries.at(j).get_continent_name().compare(af) == 0 && i == 3) {
				print(j);
			}
			if (countries.at(j).get_continent_name().compare(as) == 0 && i == 4) {
				print(j);
			}
			if (countries.at(j).get_continent_name().compare(au) == 0 && i == 5) {
				print(j);
			}

		}
	}*/
}

//void MapObserver::print(int i) {
//	std::cout << "\nCOUNTRY: " + countries.at(i).get_country_name() << std::endl;
//	std::cout << "OWNER: " + countries.at(i).get_owner_name() << std::endl;
//	std::cout << "ARMIES: " << countries.at(i).get_number_of_armies() << std::endl;
//
//	std::vector<Country*> adjacencies = countries.at(i).getConnectedCountries();
//	std::cout << "ADJACENCIES: ";
//	for (int i = 0; i < adjacencies.size(); i++) {
//		if (i != adjacencies.size() - 1) {
//			std::cout << adjacencies.at(i)->get_country_name() + ", ";
//		}
//		else { std::cout << adjacencies.at(i)->get_country_name() << std::endl; }
//	}
//}