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
	cout << "PLAYER VALUES HAVE BEEN UPDATED" << endl;
	cout << "NAME: " << playerName << endl;
	cout << "COUNTRIES OWNED: "<< endl<<_player->print_CountryList();
	cout << "CONTINENTS OWNED: " << endl << _player->print_ContinentList() << endl;
	cout << "REINFORCEMENTS/TURN " << _player->numberOfReinforcements() << endl;
	cout << "TOTAL ARMIES: " << _player->total_number_of_armies_owned() << endl;
	cout << "BATTLES WON: " << _player->getBattlesWon()<< endl<<endl;
};