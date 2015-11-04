#include "stdafx.h"
#include "Engine.h"


Engine::Engine()
{
	cout << "Assignment: creating engine and game state" << endl;
	gameState = GameState("Person"); // maybe ask the user for his name?
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
		reinforcementPhase();
		attackPhase();
		fortificationPhase();
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
		vector<Player> v = gameState.getAIPlayers();
		for (unsigned int i = 0; i < v.size(); ++i) {


			if (v[i].numberOfCountriesOwned() < 1)
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
	//TODO **********************************************************************************************************************
	// ask here the user for number of players
	
	gameState.addPlayer("AI Mister Swag");
	gameState.addPlayer("AI Mister Yolo");
	gameState.addPlayer("AI Miss Swag");
	gameState.addPlayer("AI Miss Yolo");
	
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
	gameState.generateCountries();
}




