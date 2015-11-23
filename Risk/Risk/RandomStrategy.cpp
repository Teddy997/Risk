#include "RandomStrategy.h"



RandomStrategy::RandomStrategy()
{
}

void RandomStrategy::attack(Player* p1, Player* p2) {
	cout << "random attacking" << endl;

	for (Country* c1 : p1->getCountries()) {
		bool usedC1 = false;
		vector<Country*> connectedCountries = c1->getConnectedCountries();
		for (Country* c2 : connectedCountries) {

			//bool superiority = c1->get_number_of_armies() / c2->get_number_of_armies();
			if (c1->getOwner() != c2->getOwner()) {
				usedC1 = true;
				// attacking 
				Combat::combat(*c1, *c2, false, 1, 9, 9);

			}
			if (usedC1)
				break;
		}
	}

}
RandomStrategy::~RandomStrategy()
{
}
