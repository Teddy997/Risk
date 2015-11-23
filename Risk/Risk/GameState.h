#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Map.h"
#include "Deck.h"
#include "AgressiveStrategy.h"
#include "DefensiveStrategy.h"
#include "RandomStrategy.h"
#include "NoStrategy.h"
#include "InputProcedure.h"
#include "MapCreator.h"
using namespace std;

enum Phase { // Keeps track of the phase we are currently in.

	REINFORCING, 
	ATTACKING,
	FORTIFYING
};
class GameState
{
public:

	GameState();
	GameState(std::string name); // initializes the player with a name
	GameState(bool loading);
	~GameState();
	// adds a player to the game and sets its strategy randomly between aggressive, defensive and random
	void addPlayer(std::string name); 
	void setPlayer(Player* p);
	void setAIPlayers(std::vector<Player*> ais);
	void changeGamePhase(Phase newPhase);
	void setGamePhase(Phase newPhase) { currentPhase = newPhase; }
	Phase const getGamePhase() { return currentPhase; }
	
	void removePlayerAtIndex(int i);

	void updatePlayerTurn(int turn); // changes the current player to the player after it

	Player* getMainPlayer(); // returns the human player

	Player* getCurrentPlayer(); // returns the current player

	vector<Player*> getAIPlayers(); // returns the AI players

	Map* getMap() { return map; }

	Deck* const getDeck() { return deck; }
	void setDeck(Deck* d) { deck = d; }
	void setMap(string str); // initializes the map
	void setMap(Map* m);

	void displayMapDirectoryContents();

	void displaySaveDirectoryContents();

	// assignCountries() assigns countries randomly to the player.
	void assignCountries();

	std::string phaseToString();
	
	bool getBrandNewGame() { return brandNewGame; }
	
	std::string unbuild();

	GameState build(std::string line);
	
private:
	Player* player;
	vector<Player*> AIPlayers;
	Map* map;
	Deck* deck;
	Phase currentPhase;
	void reinforcingPhase();
	void fortifyingPhase();
	void attackingPhase();
	
	void updateView();
	int getIndexOfCountry();
	int getArmies(int max);
	Player* currentPlayer;
	void doAIReinforcement(int armies);
	void doAIFortification();
	void doAIAttacking();
	void setPlayerTurn(Player* p);
	void manageMap();
	bool brandNewGame;

	class UnBuilder {
	private:
		class GameState* gs;
	public:
		UnBuilder(GameState* gs);
		~UnBuilder();
		std::string unbuild();
	};

	class Builder {
	private:
		std::string blueprint;
		std::string map_name_tobuild;
		Map* map_tobuild;
		int num_of_players_tobuild;
		Player* player_tobuild;
		vector<Player*> ai_players_tobuild;
		Player* current_player_tobuild;
		Phase currentPhase_tobuild;
		Deck* current_deck_tobuild;
		std::vector<std::string> split(std::string s, char d);
	public:
		Builder(std::string bp);
		void setMapName_tobuild(std::string line);
		void setMap_tobuild();
		void setNumOfPlayers_tobuild(std::string line);
		void setPlayer_tobuild(std::string line);
		void setAIPlayers_tobuild(std::string line);
		void setCurrentPlayer_tobuild(std::string line);
		void setCurrentPhase_tobuild(std::string line);
		void setCurrentDeck_tobuild(std::string line);
		
		GameState build();
	};
};

