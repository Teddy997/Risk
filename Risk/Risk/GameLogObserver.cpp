#include "GameLogObserver.h"

GameLogObserver::GameLogObserver() {

}
GameLogObserver:: ~GameLogObserver() {
	game->Detach(this);
}
void GameLogObserver:: update() {
	display();
}
void GameLogObserver :: display() {

}