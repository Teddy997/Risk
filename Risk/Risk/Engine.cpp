
#include "Engine.h"

using namespace std;
Engine::Engine()
{
	cout << "Starting the program..." << endl;
	cout << "Welcome to Risk!" << endl;
	cout << "Made with great love by Cynthia, Eric, Robert and Radu\n" << endl;

	cout << "Please enter your name" << endl;

	string name = "";
	cin >> name;
	gameState = GameState(name); // the name of the human player
	startPhase();
	
}


Engine::~Engine()
{
}

void Engine::startPhase() {
	chooseMap();
	generateAIPlayers();
	assignCountries();
	gamePlayPhase();
}

void Engine::gamePlayPhase(){
	cout << "Starting the Game!!!" << endl;
	unsigned int turn = 1;
	while (victoryConditions()) {
		cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
		cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
		cout << "current player's turn: " << gameState.getCurrentPlayer()->get_player_name() << endl;
		cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
		cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
		reinforcementPhase();
		//attackPhase();
		fortificationPhase();
		if (turn > gameState.getAIPlayers().size())
			turn = 0;
		gameState.updatePlayerTurn(++turn);
		
	}

}



void Engine::reinforcementPhase() {
	cout << "Reinforcing..." << endl;
	gameState.changeGamePhase(Phase(REINFORCING));

	cout << "done.\n" << endl;

}
void Engine::attackPhase() {
	cout << "Attacking...\n" << endl;
	gameState.changeGamePhase(Phase(ATTACKING));

	cout << "done.\n" << endl;
}
void Engine::fortificationPhase() {
	cout << "Fortifying...\n" << endl;
	gameState.changeGamePhase(Phase(FORTIFYING));
	cout << "done.\n" << endl;

}





bool Engine::victoryConditions() {
	
	cout << "Checking to see if the user has won or lost the game" << endl;
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
	cout << "Generating AI players...\n" << endl;
	vector<string> names = { "AI Michonne", "AI Jon Snow", "AI Heisenberg" };
	// asking playa for number of players.
	unsigned int opponents = 0;
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

	cout << "done.\n" << endl;
}

void Engine::chooseMap() {
	cout << "Choosing the map...\n" << endl;
	string s = "default";
	gameState.displayMapDirectoryContents();
	cout << "Please type the name of the map you want to play." << endl;
	
	bool valid = false;
	while (valid == false) {
		getline(cin, s);
		//Checking whether the map chosen is correct by seeing if countries opens
		string dirname = "Maps//" + s + "//countries.txt"; 
		std::fstream filestr;
		//If it does open, then the path is valid, and we can choose this map
		filestr.open(dirname);
		if (filestr.is_open()) {
			filestr.close();
			valid = true;
		}
		else { cout << "This map doesn't exist!" << endl; }
	}
	
	gameState.setMap(s);
	cout << "done.\n" << endl;
}


void Engine::assignCountries() {
	cout << "Assigning countries to players... \n" << endl;
	gameState.assignCountries();
	cout << "done.\n" << endl;
}




