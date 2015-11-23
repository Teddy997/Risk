#include "AgressiveStrategy.h"



AgressiveStrategy::AgressiveStrategy()
{
}

void AgressiveStrategy::attack(Player* p1,Player* p2) {
	cout << "agressively owning with player "<< p1->get_player_name() << endl;
	
	for (Country* c1 : p1->getCountries()) {
		bool usedC1 = false;
		vector<Country*> connectedCountries = c1->getConnectedCountries();
		for (Country* c2 : connectedCountries) {
			
			bool superiority = c1->get_number_of_armies() > c2->get_number_of_armies();
			if (c1->getOwner() != c2->getOwner() && superiority) {
				usedC1 = true;
				// attacking with all the armies available in the country of the aggressive AI (because he's aggressive)
				Combat::combat(*c1, *c2, false, 1, 9, 9); // '9' means all the available countries
				
			}
			if (usedC1)
				break;
		}
	}
}

AgressiveStrategy::~AgressiveStrategy()
{
}
