

#include <iostream>
#include "card.h"
#include "player.h"
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include <stack> // for deck of cards
#include <ctime> // std::time
#include <algorithm>// std::random_shuffle
#include <chrono> //sleep method
#include <thread>//sleep method

/*stuff to do
1.Show the dealer's play
2.hide dealer's 2nd card on first hand until dealer's play
3.reformat using iomnaip
4.create a make file
5.Upload to Github and put on resume*/
int get_total(const std::vector<Card> &hand) /*
											 considering a default parameter
											 to put in the user's total*/
{
	int i = 0; 
	for(Card c: hand) // every card in hand
	{ 
		i += c.get_integer_value();
	}
	return i; // return the card value
			 // important logic needs to be made for A suit *** to be done 
}

void show_hand(const std::vector<Card> &hand, std::string player_type) // player_type -> player/dealer
{
	std::cout << player_type << " hand: ";
	for (auto c : hand)
		std::cout << c.get_card() << "\t";
	std::cout << "\n";

}

void deal_cards(std::vector<Card> &hand, std::stack<Card> &deck)
{ // in first round
	for (int i = 0; i < 2; i++) // deal two cards 
	{
		Card c = deck.top(); // get card from top of deck
		hand.push_back(c); // put card in hand
		deck.pop();// remove card from top of the deck
	}
}
void hit(std::vector<Card> &hand, std::stack<Card> &deck) // can be used to hit and for dealers play
{

	Card c = deck.top();
	hand.push_back(c);
	deck.pop();
}
void dealers_play(const int &bet_amount, std::vector<Card> &player_hand, std::vector<Card> dealer_hand, int &player_balance,std::stack<Card> &deck)
// player_total->(card total value) player_balance->monetary balance 
{
	/*3 Outcomes->player loses: subtract from player balance, and output the result
				  player ties: nothing happens, no money is lost or won, output the result
				  player wins: add to player balance and output the result
				  Also, for end of game stats:
				  Dealer's balance starts at 0, and will be outputted at the end 
	*/		  
	int player_total = get_total(player_hand), dealer_total = get_total(dealer_hand);
	if (player_total > 21) // player  loses
	{
		player_balance -= bet_amount;
		std::cout << "You lose this round" << std::endl;
	}

	while (dealer_total < 17) // dealer must keep hitting until they hit 16 then they stand
	{
		hit(dealer_hand, deck); // 1.add card to dealer's hand
		//show dealer's card
		dealer_total = get_total(dealer_hand); // 2. calculate total
		std::cout << "Dealer's total: " << get_total(dealer_hand) << std::endl; //output total

		if (dealer_total > 21) // busts
		{
			player_balance += bet_amount;
			std::cout << "BUST! You won this hand!" << std::endl;
			return;
			//dealer loses
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	} // the cards have stopped dealing, now we do some math
	  // 3. Adjust balance as needed
	if (player_total > dealer_total)
		//player wins
	{
		std::cout << "YOU WON THIS HAND!" << std::endl;
		player_balance += bet_amount;
	}
	 
	else if (player_total < dealer_total)
		//player loses
	{
		std::cout << "YOU LOSE THIS HAND!" << std::endl;
		player_balance -= bet_amount;
	}
	else
		//tie nothing happens
		std::cout << "DRAW!" << std::endl;
	
}


int main()
{
	// 8 decks of cards
	srand(time(0)); // seed
	std::vector<std::string> different_suits = { "D","H","S","C" }; // diamonds, hearts, spades, clubs
	std::vector<std::string> different_faces = { "A","2","3","4","5","6","7","8","9","10","J","Q","K" }; // face values
	std::vector<int> integer_values = { 11,2,3,4,5,6,7,8,9,10,10,10,10 }; // 10,J,Q,K
	std::vector<Card> shuffle_deck;
	std::stack<Card> deck_of_cards;
	std::vector<Card> player_hand, dealer_hand; // your hand and dealer's hand
	char input_control;
	int balance = 10000, current_bet,temp_total; // player starts with 10,000, temp_total is the current total of a hand
	std::string player_name;
	bool first_deal_flag = true, bet_locked_in_flag = true, exit_flag = false; // 
	// first_deal_flag -> Only deals 2 cards once per round
	// bet_locked_in_flag -> Once you lock in a bet for a round, don't change it
	//exit_flag -> for when the player goes over 21 before they stand
	/* will have to put conditions on the first deal and lock in the bet 
	so the cpu isn't aaking for a new bet every round or dealing 2 cards every round
	*/
	for (int a = 0; a < 8; a++)
		for (int i = 0; i < different_suits.size(); i++) // create our deck of cards
			for (int j = 0; j < different_faces.size(); j++)
			{
				Card temp(different_suits[i], different_faces[j], integer_values[j]);
				shuffle_deck.push_back(temp); // push the card into the deck
			}
	std::random_shuffle(shuffle_deck.begin(), shuffle_deck.end()); // shuffle the deck O(n) run time
	// check if cards are in the deck
	for (Card c : shuffle_deck)
	{
		deck_of_cards.push(c); // push the cards into the stack after shuffling for O(1) removing
		std::cout << c.get_suit() << c.get_face() << std::endl;
	} //

	// deal the cards

	std::cout << "Enter 'S' to start playing" << std::endl;
	std::cin >> input_control;
	if (input_control == 'S')
	{
		std::cout << "Enter a name" << std::endl;
		std::cin >> player_name;
		Player user_one(player_name); // create the player
		while (balance>0) // game plays until player decides to quit or they're broke
		{	
			/*std::cout << "Enter Q to quit, enter any other key to keep playing" << std::endl;
			std::cin >> input_control;
			if (input_control == 'Q')
				break;
				*/
			if (bet_locked_in_flag)
			{
				std::cout << "NEW ROUND!" << std::endl;
				std::cout << "Enter in whole dollars how much you want to bet this round \n (You cannot bet more than you have)" << std::endl;
				std::cin >> current_bet; // get bet
				while (current_bet > balance || current_bet <= 0)
				{
					std::cout << "Invalid bet you cannot bet more than you have or bet 0 or less dollars.\n Enter bet again" << std::endl;
					std::cin >> current_bet;
				}
				bet_locked_in_flag = false; // the bet has been locked in
			}
			user_one.set_bet_amount(current_bet);
			//deal cards
			if (first_deal_flag)
			{
				deal_cards(player_hand, deck_of_cards); // only once per round
				deal_cards(dealer_hand, deck_of_cards); // only once per round
				first_deal_flag = false; // the cards have been dealt
			}
			// format to look good
			/*std::cout << "Your hand:\t" << player_hand[0].get_card() << "\t" << player_hand[1].get_card() << std::endl;
			
			std::cout << "Dealer hand:\t" << dealer_hand[0].get_card() << "\t" << "?" << std::endl;
			*/
			show_hand(player_hand, player_name); // show player's hand
			temp_total = get_total(player_hand);
			std::cout << "Your total: " << temp_total << std::endl;
			show_hand(dealer_hand, "Dealer");
			temp_total = get_total(dealer_hand);
			std::cout << "Dealer's total: " << temp_total << std::endl;

			std::cout << "Enter 'S' for stand, 'H' to hit, or 'D' to double your bet" << std::endl;
			
			std::cin >> input_control;
			// while loop until user stands or busts 
			switch (input_control)
			{
			case 'S': std::cout << "You decided to stand" << std::endl;
				dealers_play(user_one.get_bet_amount(), player_hand, dealer_hand,balance,deck_of_cards);  //std::cout << "You decided to stand" << std::endl; // Stand function, initiates dealer play
				//might break
				first_deal_flag = true;
				bet_locked_in_flag = true;
				player_hand.clear(); // clear the hands
				dealer_hand.clear(); // clear the hands
				break;
			case 'H': std::cout << "You decided to hit" << std::endl;
				hit(player_hand, deck_of_cards);  // hit function add a card to hand
				if (get_total(player_hand) > 21) // you lose
				{
					exit_flag = true;
					std::cout << "You LOSE!";
					balance -= current_bet;
					first_deal_flag = true;
					bet_locked_in_flag = true;
					player_hand.clear(); // clear the hands
					dealer_hand.clear(); // clear the hands
				}
				break;
			case 'D': 
				if (balance >= user_one.get_bet_amount() * 2)
				{
					user_one.set_bet_amount(user_one.get_bet_amount() * 2);
					std::cout << "You doubled your bet to " << user_one.get_bet_amount() << std::endl;
				}
				else
					std::cout << "You don't have enough $$$ to double your bet" << std::endl;
				//write pre-condition where you can't double your bet to more than you have***
				//std::cout << "You decided to double your bet" << std::endl; // doubles bet
				break;
			}
			
			//switch case for hit stand and double 
			//output player's balance
			std::cout << balance << " Balance: " << balance << std::endl;

			std::cout << "Enter Q to quit, enter any other key to keep playing" << std::endl;
			std::cin >> input_control;
			if (input_control == 'Q')
				break;
			
		}
	}
	std::cout << "'Test': Game has exited" << std::endl;
	//std::cout << deck_of_cards[0].get_suit() << deck_of_cards[0].get_face() << std::endl;
	//if player's balance == 0, let em know they're broke

	std::cout << "This thang runs" << std::endl;
	std::cin.get();
	return 0;
}
