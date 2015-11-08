#include "playerView.h"
#include <iostream>
using namespace std;

playerView::playerView() {

};
playerView::playerView(Player* p) {
// upon initialization , attaches itself to a player
	_player = p;
	_player->Attach(this);
};
playerView::~playerView() {
// upon destruction it detaches itself from its player
	_player->Detach(this);
};
void playerView::Update() {
	display();
};
void playerView::display() {
	string playerName = _player->get_player_name();

	cout << "Player Name: " << playerName << endl;
	
	cout << "List of countries Owned: "<< endl<<_player->print_CountryList()<<endl;
	cout << "List of continents Owned: " << endl << _player->print_ContinentList() << endl;
	cout << "Number of Reinforcements: " << _player->numberOfReinforcements() << endl;
	cout << "Number of Armies: " << _player->total_number_of_armies_owned() << endl;
	cout << "Number of Battles Won: " << _player->getBattlesWon()<< endl<<endl;

};