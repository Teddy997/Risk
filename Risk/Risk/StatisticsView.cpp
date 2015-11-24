#include "StatisticsView.h"



StatisticsView::StatisticsView()
{
}


StatisticsView::~StatisticsView()
{
	gameState->Detach(this);
}

StatisticsView::StatisticsView(GameState* game) {
	// upon initialization , attaches itself to a player
	gameState = game;
	//gameState->Attach(this);
}

void StatisticsView::Update() {
	display();
}

void StatisticsView::display() {
	ofstream out;
	out.open("Statistics.txt", std::ios_base::app);
	vector<Player*> AIPlayers = gameState->getAIPlayers();
	out << "===========================================NEW TURN==========================================" << endl;
	out << gameState->getMainPlayer()->get_player_name() << "'s countries: " << endl;
	out << gameState->getMainPlayer()->print_countries_owned() << endl;
	out << "Armies owned: " << gameState->getMainPlayer()->total_number_of_armies_owned() << endl;
	out << "Number of cards: " << gameState->getMainPlayer()->getNumberOfCards() << endl;
	out << endl;

	for (Player* p : AIPlayers) {
		out << p->get_player_name() << "'s countries: " << endl;
		out << p->print_countries_owned() << endl;
		out << "Armies owned: " << p->total_number_of_armies_owned() << endl;
		out << "Number of cards: " << p->getNumberOfCards() << endl;
		out << endl;
	}





	out.close();



}
