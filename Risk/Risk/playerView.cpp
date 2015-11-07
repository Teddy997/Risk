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

	cout << "PLayer Name: " << playerName << endl;
	_player->print_countries_owned();
};