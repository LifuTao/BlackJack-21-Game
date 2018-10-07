#include <iostream>
#include "player.h"


Player::Player(std::string name)
{
	player_name = name;
	//current_balance = 10000;
}
std::string Player::get_player_name()
{
	return player_name;
}
/*int Player::get_balance()
{
	return current_balance;
}*/
void Player::set_bet_amount(int amount)
{
	bet_amount = amount;
}
int Player::get_bet_amount()
{
	return bet_amount;
}


