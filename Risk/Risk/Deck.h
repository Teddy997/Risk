#ifndef DECK_H
#define DECK_H

#include <vector>
#include <string>

class Deck {
public:
	struct Card {
		int card_id;

		int const get_id() { return card_id; }
	};
	
	Deck();
	~Deck();
	
	Deck::Card draw_card();
	void return_card(Card card);
	std::vector<Card> const get_current_deck() { return current_deck; }
	void set_deck(std::vector<Card> d) { current_deck = d; }
private:
	/*Member variables*/
	static const int max_deck_size = 30;
	std::vector<Card> current_deck;
	
	/*Member functions*/
	void initialize_deck();
	void shuffle_deck();
};

#endif