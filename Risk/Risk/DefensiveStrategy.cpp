#include "DefensiveStrategy.h"



//DefensiveStrategy::DefensiveStrategy()
//{
//	stratName = "Defensive Strategy";
//}

void DefensiveStrategy::attack(Player* p1, Player* p2) {
	cout << "defenssively winning" << endl;
	if (p1->get_player_name() == "AI Heisenberg") {
		vector<Country*> c = p1->getCountries()[4]->getConnectedCountries();
		for (int i = 0; i < c.size(); ++i)
			cout << "connected country of " << p1->get_country(4)->get_country_name() << " is " << c[i]->get_country_name() << endl;
	}
	for (Country* c1 : p1->getCountries()) {
		bool usedC1 = false;
		vector<Country*> connectedCountries = c1->getConnectedCountries();
		for (Country* c2 : connectedCountries) {

			int superiority = c1->get_number_of_armies() / c2->get_number_of_armies();
			if (c1->getOwner() != c2->getOwner() && superiority >= 2) { // check if the armies outnumber 2:1
				usedC1 = true;
				// attacking
				Combat::combat(*c1, *c2, false, 1, 9, 9);

			}
			if (usedC1)
				break;
		}
	}
}
DefensiveStrategy::~DefensiveStrategy()
{
}
