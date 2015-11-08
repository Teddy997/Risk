#pragma once

#include "observer.h"
#include "Player.h"
class playerView : public Observer {
public:
	playerView();
	playerView(Player* p);
	~playerView();
	void Update();
	void display();
private:
	Player* _player;
};