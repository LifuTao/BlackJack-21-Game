#ifndef PLAYER_H
#define PLAYER_H


#include <iostream>
#include <cstdlib> //provides size_t
#include <stdexcept> //provides runtime errors
#include <string>
#include <vector>
#include "card.h"
class Player
{
	public:
		// pLayer constructor
	Player(std::string name); // if no name is given then name is "Player One"

	std::string get_player_name();
	//get the player's  name
	//int get_balance();
	// returns the blanace
	void stand();
	// keep your cards, the game is now decided by what card the dealer gets
	void double_bet();
	// double the current bet
	void hit();
	// get another card and add to the current hand (our vector)
	int get_card_total();
	// return the card_total the player has-->crucial to the game ***
	void set_bet_amount(int amount);
	// sets the bet amount
	int get_bet_amount();

	private:
		std::vector<int> hand;
		//int current_balance; // players start with 10,000
		std::string player_name;
		int bet_amount;
};
#endif // !
