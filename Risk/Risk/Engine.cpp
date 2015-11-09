#include "stdafx.h"
#include "Engine.h"

using namespace std;
Engine::Engine()
{
	
	cout << "Please enter your name" << endl;

	string name = "";
	cin >> name;
	gameState = GameState(name);
	startPhase();
	
}


Engine::~Engine()
{
}

void Engine::startPhase() {
	cout << "Assignment: starting game..." << endl;
	generateAIPlayers();
	chooseMap();
	assignCountries();
	gamePlayPhase();
}

void Engine::gamePlayPhase(){
	cout << "Assignment: playing the game!" << endl;
	while (victoryConditions()) {
		cout << "current player's turn: " << gameState.getCurrentPlayer()->get_player_name() << endl;
		unsigned int turn = 0;
		reinforcementPhase();
		attackPhase();
		fortificationPhase();
		if (turn > gameState.getAIPlayers().size())
			turn = 0;
		gameState.updatePlayerTurn(++turn);
		
	}

}



void Engine::reinforcementPhase() {
	cout << "Assignment: Reinforcing..." << endl;
	gameState.changeGamePhase(Phase(REINFORCING));


}
void Engine::attackPhase() {
	cout << "Assignment: Attacking..." << endl;
	gameState.changeGamePhase(Phase(ATTACKING));


}
void Engine::fortificationPhase() {
	cout << "Assignment: Fortifying..." << endl;
	gameState.changeGamePhase(Phase(FORTIFYING));


}





bool Engine::victoryConditions() {
	
	cout << "Assignment: Checking to see if anybody won " << endl;
	if (gameState.getCurrentPlayer()->numberOfCountriesOwned() < 1)
		defeat = true;
	else {
		bool d = false;
		vector<Player*> v = gameState.getAIPlayers();
		for (unsigned int i = 0; i < v.size(); ++i) {
			

			if (v[i]->numberOfCountriesOwned() < 1)
				victory = true;
			else {
				victory = false;
				d = true;
			}
			if (d)
				break;

		}

	}

	if (defeat || victory)
		return false;
	else
		return true;
}
void Engine::generateAIPlayers() {
	cout << "Assignment: Generating AI players..." << endl;
	vector<string> names = { "AI Michonne", "AI Jon Snow", "AI Heisenberg" };
	// asking playa for number of players.
	int opponents = 0;
	cout << "Choose the number of opponents to play against. For the sake of simplicity and coherence, please only"
		<< " choose a number between 1 and " << names.size() << endl;
	bool valid = false;

	while (valid == false) {
		opponents = InputProcedure::get_choice();
		if (opponents < 1 || opponents > names.size()) {
			cout << "Not a valid choice." << endl;
		}
		else {
			valid = true;
		}
	}

	if (valid) {
		for (unsigned int i = 0; i < names.size(); ++i) {
			if (opponents > 0) {
				gameState.addPlayer(names[i]);
				--opponents;
			}
		}
	}

	
}

void Engine::chooseMap() {
	cout << "Assignment: Choosing the map..." << endl;
	//TODO **********************************************************************************************************************
	// choose the map to play on
	// countries will be generated inside the map class
	string s = "Default_Map";
	gameState.setMap(s);
}


void Engine::assignCountries() {
	cout << "Assignment: assigning countries to players... " << endl;
	gameState.assignCountries();
}




