#include "StatisticsWorld.h"



StatisticsWorld::StatisticsWorld()
{
}


StatisticsWorld::~StatisticsWorld()
{
}

void StatisticsWorld::Update() {
	
	StatisticsDecorator::Update();
	GameState* gameState = view->getGameState();
	
	ofstream out;
	out.open("Statistics.txt", std::ios_base::app);
	out << endl;
	out << "*********World Statistics**********" << endl;
	int totalNumberOfCountries = 0;
	int c1 = gameState->getMainPlayer()->numberOfCountriesOwned();
	int c2 = 0;
	vector<Player*> AIPlayers = gameState->getAIPlayers();
	for (Player* p : AIPlayers) {
		c2 += p->numberOfCountriesOwned();
		
	}
	totalNumberOfCountries = c1 + c2;
	double percentageForHuman = (double)c1 / totalNumberOfCountries * 100;
	out << "This is the percentage of the world owned by: " << gameState->getMainPlayer()->get_player_name() << ": " << percentageForHuman << "%" << endl;

	for (Player* p : AIPlayers) {
		int c3 = p->numberOfCountriesOwned();
		double percentageForAI = (double)c3 / totalNumberOfCountries * 100;
		out << "This is the percentage of the world owned by: " << p->get_player_name() << ": " << percentageForAI<< "%" << endl;
	}

	out.close();
}